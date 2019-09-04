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
union kds_ptr {scalar_t__ raw; } ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct kd_storage {int kds_bufindx; int /*<<< orphan*/  kds_bufcnt; TYPE_1__* kds_records; } ;
struct kd_bufinfo {union kds_ptr kd_list_tail; } ;
struct TYPE_4__ {int debugid; uintptr_t arg1; uintptr_t arg2; uintptr_t arg3; uintptr_t arg4; uintptr_t arg5; } ;
typedef  TYPE_1__ kd_buf ;
struct TYPE_5__ {int kdebug_slowcheck; int kdebug_flags; scalar_t__ enabled; scalar_t__ kds_inuse_count; } ;

/* Variables and functions */
 int BSC_SysCall ; 
 scalar_t__ DBG_TRACE ; 
 int EVENTS_PER_STORAGE_UNIT ; 
 scalar_t__ FALSE ; 
 int INTERRUPT ; 
 int KDBG_CSC_MASK ; 
 int KDBG_EVENTID_MASK ; 
 scalar_t__ KDBG_EXTRACT_CLASS (int) ; 
 int KDBG_FLAG_FILTERED ; 
 int KDBG_FLAG_NOPROCFILT ; 
 int KDBG_RANGECHECK ; 
 int KDBG_TIMESTAMP_MASK ; 
 int KDBG_TYPEFILTER_CHECK ; 
 int KDBG_VALCHECK ; 
 int KDEBUG_ENABLE_PPT ; 
 int KDEBUG_ENABLE_TRACE ; 
 scalar_t__ KDS_PTR_NULL ; 
 int MACH_SysCall ; 
 int MACH_vmfault ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSCompareAndSwap (int,int,int*) ; 
 struct kd_storage* POINTER_FROM_KDS_PTR (union kds_ptr) ; 
 int SLOW_NOLOG ; 
 scalar_t__ allocate_storage_unit (int) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 TYPE_3__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_set_timestamp_and_cpu (TYPE_1__*,int,int) ; 
 int kdbg_timestamp () ; 
 int /*<<< orphan*/  kdbg_typefilter ; 
 int /*<<< orphan*/  kdbg_wakeup () ; 
 struct kd_bufinfo* kdbip ; 
 int /*<<< orphan*/  kdebug_debugid_procfilt_allowed (int) ; 
 int kdebug_enable ; 
 int kdlog_beg ; 
 int kdlog_end ; 
 int kdlog_value1 ; 
 int kdlog_value2 ; 
 int kdlog_value3 ; 
 int kdlog_value4 ; 
 scalar_t__ kds_waiter ; 
 int /*<<< orphan*/  ml_at_interrupt_context () ; 
 scalar_t__ n_storage_threshold ; 
 scalar_t__ typefilter_is_debugid_allowed (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
kernel_debug_internal(
	uint32_t debugid,
	uintptr_t arg1,
	uintptr_t arg2,
	uintptr_t arg3,
	uintptr_t arg4,
	uintptr_t arg5,
	uint64_t flags)
{
	uint64_t now;
	uint32_t bindx;
	kd_buf *kd;
	int cpu;
	struct kd_bufinfo *kdbp;
	struct kd_storage *kdsp_actual;
	union kds_ptr kds_raw;
	bool only_filter = flags & KDBG_FLAG_FILTERED;
	bool observe_procfilt = !(flags & KDBG_FLAG_NOPROCFILT);

	if (kd_ctrl_page.kdebug_slowcheck) {
		if ((kd_ctrl_page.kdebug_slowcheck & SLOW_NOLOG) ||
		    !(kdebug_enable & (KDEBUG_ENABLE_TRACE | KDEBUG_ENABLE_PPT)))
		{
			goto out1;
		}

		if (!ml_at_interrupt_context() && observe_procfilt &&
				!kdebug_debugid_procfilt_allowed(debugid)) {
			goto out1;
		}

		if (kd_ctrl_page.kdebug_flags & KDBG_TYPEFILTER_CHECK) {
			if (typefilter_is_debugid_allowed(kdbg_typefilter, debugid))
				goto record_event;

			goto out1;
		} else if (only_filter) {
			goto out1;
		}
		else if (kd_ctrl_page.kdebug_flags & KDBG_RANGECHECK) {
			/* Always record trace system info */
			if (KDBG_EXTRACT_CLASS(debugid) == DBG_TRACE)
				goto record_event;

			if (debugid < kdlog_beg || debugid > kdlog_end)
				goto out1;
		}
		else if (kd_ctrl_page.kdebug_flags & KDBG_VALCHECK) {
			/* Always record trace system info */
			if (KDBG_EXTRACT_CLASS(debugid) == DBG_TRACE)
				goto record_event;

			if ((debugid & KDBG_EVENTID_MASK) != kdlog_value1 &&
			    (debugid & KDBG_EVENTID_MASK) != kdlog_value2 &&
			    (debugid & KDBG_EVENTID_MASK) != kdlog_value3 &&
			    (debugid & KDBG_EVENTID_MASK) != kdlog_value4)
				goto out1;
		}
	} else if (only_filter) {
		goto out1;
	}

record_event:
	disable_preemption();

	if (kd_ctrl_page.enabled == 0)
		goto out;

	cpu = cpu_number();
	kdbp = &kdbip[cpu];

#if KDEBUG_MOJO_TRACE
	if (kdebug_enable & KDEBUG_ENABLE_SERIAL)
		kdebug_serial_print(cpu, debugid,
				    kdbg_timestamp() & KDBG_TIMESTAMP_MASK,
				    arg1, arg2, arg3, arg4, arg5);
#endif

retry_q:
	kds_raw = kdbp->kd_list_tail;

	if (kds_raw.raw != KDS_PTR_NULL) {
		kdsp_actual = POINTER_FROM_KDS_PTR(kds_raw);
		bindx = kdsp_actual->kds_bufindx;
	} else {
		kdsp_actual = NULL;
		bindx = EVENTS_PER_STORAGE_UNIT;
	}

	if (kdsp_actual == NULL || bindx >= EVENTS_PER_STORAGE_UNIT) {
		if (allocate_storage_unit(cpu) == FALSE) {
			/*
			 * this can only happen if wrapping
			 * has been disabled
			 */
			goto out;
		}
		goto retry_q;
	}

	now = kdbg_timestamp() & KDBG_TIMESTAMP_MASK;

	if ( !OSCompareAndSwap(bindx, bindx + 1, &kdsp_actual->kds_bufindx))
		goto retry_q;

	kd = &kdsp_actual->kds_records[bindx];

	kd->debugid = debugid;
	kd->arg1 = arg1;
	kd->arg2 = arg2;
	kd->arg3 = arg3;
	kd->arg4 = arg4;
	kd->arg5 = arg5;

	kdbg_set_timestamp_and_cpu(kd, now, cpu);

	OSAddAtomic(1, &kdsp_actual->kds_bufcnt);

#if KPERF
	kperf_kdebug_callback(debugid, __builtin_frame_address(0));
#endif
out:
	enable_preemption();
out1:
	if (kds_waiter && kd_ctrl_page.kds_inuse_count >= n_storage_threshold) {
		uint32_t	etype;
		uint32_t	stype;

		etype = debugid & KDBG_EVENTID_MASK;
		stype = debugid & KDBG_CSC_MASK;

		if (etype == INTERRUPT || etype == MACH_vmfault ||
		    stype == BSC_SysCall || stype == MACH_SysCall) {
			kdbg_wakeup();
		}
	}
}