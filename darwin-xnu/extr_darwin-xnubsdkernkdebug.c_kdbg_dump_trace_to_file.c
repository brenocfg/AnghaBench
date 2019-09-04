#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct TYPE_4__ {int debugid; size_t arg1; int arg2; int /*<<< orphan*/  arg5; } ;
typedef  TYPE_1__ kd_buf ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int FWRITE ; 
 int /*<<< orphan*/  KDBG_RELEASE (int) ; 
 int KDEBUG_ENABLE_TRACE ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int O_CREAT ; 
 int O_NOFOLLOW ; 
 int /*<<< orphan*/  RAW_VERSION1 ; 
 int /*<<< orphan*/  RAW_file_offset ; 
 int TRACE_WRITING_EVENTS ; 
 int VNOP_FSYNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commpage_update_kdebug_state () ; 
 int /*<<< orphan*/  cpu_number () ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_3__ kd_ctrl_page ; 
 int kdbg_read (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_set_timestamp_and_cpu (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_timestamp () ; 
 int /*<<< orphan*/  kdbg_write_thread_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_write_to_vnode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kdebug_enable ; 
 scalar_t__ ktrace_get_owning_pid () ; 
 int /*<<< orphan*/  ktrace_lock () ; 
 int /*<<< orphan*/  ktrace_unlock () ; 
 int nkdbufs ; 
 int /*<<< orphan*/  sync (int /*<<< orphan*/ ,void*,int*) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 int /*<<< orphan*/  vnode_close (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_open (char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
kdbg_dump_trace_to_file(const char *filename)
{
	vfs_context_t ctx;
	vnode_t vp;
	size_t write_size;
	int ret;

	ktrace_lock();

	if (!(kdebug_enable & KDEBUG_ENABLE_TRACE)) {
		goto out;
	}

	if (ktrace_get_owning_pid() != 0) {
		/*
		 * Another process owns ktrace and is still active, disable tracing to
		 * prevent wrapping.
		 */
		kdebug_enable = 0;
		kd_ctrl_page.enabled = 0;
		commpage_update_kdebug_state();
		goto out;
	}

	KDBG_RELEASE(TRACE_WRITING_EVENTS | DBG_FUNC_START);

	kdebug_enable = 0;
	kd_ctrl_page.enabled = 0;
	commpage_update_kdebug_state();

	ctx = vfs_context_kernel();

	if (vnode_open(filename, (O_CREAT | FWRITE | O_NOFOLLOW), 0600, 0, &vp, ctx)) {
		goto out;
	}

	kdbg_write_thread_map(vp, ctx);

	write_size = nkdbufs * sizeof(kd_buf);
	ret = kdbg_read(0, &write_size, vp, ctx, RAW_VERSION1);
	if (ret) {
		goto out_close;
	}

	/*
	 * Wait to synchronize the file to capture the I/O in the
	 * TRACE_WRITING_EVENTS interval.
	 */
	ret = VNOP_FSYNC(vp, MNT_WAIT, ctx);

	/*
	 * Balance the starting TRACE_WRITING_EVENTS tracepoint manually.
	 */
	kd_buf end_event = {
		.debugid = TRACE_WRITING_EVENTS | DBG_FUNC_END,
		.arg1 = write_size,
		.arg2 = ret,
		.arg5 = thread_tid(current_thread()),
	};
	kdbg_set_timestamp_and_cpu(&end_event, kdbg_timestamp(),
			cpu_number());

	/* this is best effort -- ignore any errors */
	(void)kdbg_write_to_vnode((caddr_t)&end_event, sizeof(kd_buf), vp, ctx,
			RAW_file_offset);

out_close:
	vnode_close(vp, FWRITE, ctx);
	sync(current_proc(), (void *)NULL, (int *)NULL);

out:
	ktrace_unlock();
}