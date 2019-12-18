#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  struct vnode* vnode_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int u_int ;
struct vnode {int dummy; } ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/  vc_thread; } ;
struct fileproc {TYPE_5__* f_fglob; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  kd_threadmap ;
typedef  int /*<<< orphan*/  kd_regtype ;
typedef  int /*<<< orphan*/  kd_bufinfo ;
typedef  int /*<<< orphan*/  kd_buf ;
struct TYPE_6__ {int nkdbufs; int nkdthreads; int nolog; int flags; int bufid; } ;
typedef  TYPE_1__ kbufinfo_t ;
struct TYPE_8__ {int /*<<< orphan*/  fg_offset; scalar_t__ fg_data; int /*<<< orphan*/  fg_cred; } ;
struct TYPE_7__ {int kdebug_flags; int kdebug_slowcheck; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DTYPE_VNODE ; 
 int EBADF ; 
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILEGLOB_DTYPE (TYPE_5__*) ; 
 int KDBG_BUFINIT ; 
 int KDBG_LOCKINIT ; 
 int KDBG_LP64 ; 
 int /*<<< orphan*/  KDBG_RELEASE (int,...) ; 
 unsigned int KDBG_USERFLAGS ; 
 unsigned int KDEBUG_ENABLE_PPT ; 
 unsigned int KDEBUG_ENABLE_TRACE ; 
#define  KERN_KDBUFWAIT 149 
#define  KERN_KDCPUMAP 148 
#define  KERN_KDDFLAGS 147 
#define  KERN_KDEFLAGS 146 
#define  KERN_KDENABLE 145 
#define  KERN_KDGETBUF 144 
#define  KERN_KDGETREG 143 
#define  KERN_KDPIDEX 142 
#define  KERN_KDPIDTR 141 
#define  KERN_KDREADCURTHRMAP 140 
#define  KERN_KDREADTR 139 
#define  KERN_KDREMOVE 138 
#define  KERN_KDSETBUF 137 
#define  KERN_KDSETREG 136 
#define  KERN_KDSETUP 135 
#define  KERN_KDSET_TYPEFILTER 134 
#define  KERN_KDTEST 133 
#define  KERN_KDTHRMAP 132 
#define  KERN_KDWRITEMAP 131 
#define  KERN_KDWRITEMAP_V3 130 
#define  KERN_KDWRITETR 129 
#define  KERN_KDWRITETR_V3 128 
 int /*<<< orphan*/  KTRACE_KDEBUG ; 
 int /*<<< orphan*/  RAW_VERSION1 ; 
 int /*<<< orphan*/  RAW_VERSION3 ; 
 int /*<<< orphan*/  RAW_file_offset ; 
 int SLOW_NOLOG ; 
 int TRACE_WRITING_EVENTS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copyout (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  fp_drop (int /*<<< orphan*/ ,int,struct fileproc*,int) ; 
 int fp_lookup (int /*<<< orphan*/ ,int,struct fileproc**,int) ; 
 TYPE_3__ kd_ctrl_page ; 
 int kd_mapcount ; 
 int kdbg_copyin_typefilter (int /*<<< orphan*/ ,size_t) ; 
 int kdbg_copyout_thread_map (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  kdbg_lock_init () ; 
 int kdbg_read (int /*<<< orphan*/ ,size_t*,struct vnode*,struct vfs_context*,int /*<<< orphan*/ ) ; 
 int kdbg_readcpumap (int /*<<< orphan*/ ,size_t*) ; 
 int kdbg_readcurthrmap (int /*<<< orphan*/ ,size_t*) ; 
 int kdbg_readthrmap_v3 (int /*<<< orphan*/ ,size_t,int) ; 
 int kdbg_reinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdbg_set_nkdbufs (unsigned int) ; 
 int /*<<< orphan*/  kdbg_set_tracing_enabled (int /*<<< orphan*/ ,unsigned int) ; 
 int kdbg_setpid (int /*<<< orphan*/ *) ; 
 int kdbg_setpidex (int /*<<< orphan*/ *) ; 
 int kdbg_setreg (int /*<<< orphan*/ *) ; 
 int kdbg_test (size_t) ; 
 int /*<<< orphan*/  kdbg_thrmap_init () ; 
 size_t kdbg_wait (size_t,int /*<<< orphan*/ ) ; 
 int kdbg_write_thread_map (struct vnode*,struct vfs_context*) ; 
 int /*<<< orphan*/  kdebug_enable ; 
 int /*<<< orphan*/  kernel_debug_disable () ; 
 int ktrace_configure (int /*<<< orphan*/ ) ; 
 int ktrace_get_owning_pid () ; 
 int /*<<< orphan*/  ktrace_lock () ; 
 int ktrace_read_check () ; 
 int /*<<< orphan*/  ktrace_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrace_unlock () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int nkdbufs ; 
 int /*<<< orphan*/  proc_fdlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_fdunlock (int /*<<< orphan*/ ) ; 
 int vnode_getwithref (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 

int
kdbg_control(int *name, u_int namelen, user_addr_t where, size_t *sizep)
{
	int ret = 0;
	size_t size = *sizep;
	unsigned int value = 0;
	kd_regtype kd_Reg;
	kbufinfo_t kd_bufinfo;
	proc_t p;

	if (name[0] == KERN_KDWRITETR ||
		name[0] == KERN_KDWRITETR_V3 ||
		name[0] == KERN_KDWRITEMAP ||
		name[0] == KERN_KDWRITEMAP_V3 ||
		name[0] == KERN_KDEFLAGS ||
		name[0] == KERN_KDDFLAGS ||
		name[0] == KERN_KDENABLE ||
		name[0] == KERN_KDSETBUF)
	{
		if (namelen < 2) {
			return EINVAL;
		}
		value = name[1];
	}

	kdbg_lock_init();
	assert(kd_ctrl_page.kdebug_flags & KDBG_LOCKINIT);

	ktrace_lock();

	/*
	 * Some requests only require "read" access to kdebug trace.  Regardless,
	 * tell ktrace that a configuration or read is occurring (and see if it's
	 * allowed).
	 */
	if (name[0] != KERN_KDGETBUF &&
	    name[0] != KERN_KDGETREG &&
	    name[0] != KERN_KDREADCURTHRMAP)
	{
		if ((ret = ktrace_configure(KTRACE_KDEBUG))) {
			goto out;
		}
	} else {
		if ((ret = ktrace_read_check())) {
			goto out;
		}
	}

	switch(name[0]) {
		case KERN_KDGETBUF:
			if (size < sizeof(kd_bufinfo.nkdbufs)) {
				/*
				 * There is not enough room to return even
				 * the first element of the info structure.
				 */
				ret = EINVAL;
				break;
			}

			memset(&kd_bufinfo, 0, sizeof(kd_bufinfo));

			kd_bufinfo.nkdbufs = nkdbufs;
			kd_bufinfo.nkdthreads = kd_mapcount;

			if ( (kd_ctrl_page.kdebug_slowcheck & SLOW_NOLOG) )
				kd_bufinfo.nolog = 1;
			else
				kd_bufinfo.nolog = 0;

			kd_bufinfo.flags = kd_ctrl_page.kdebug_flags;
#if defined(__LP64__)
			kd_bufinfo.flags |= KDBG_LP64;
#endif
			{
				int pid = ktrace_get_owning_pid();
				kd_bufinfo.bufid = (pid == 0 ? -1 : pid);
			}

			if (size >= sizeof(kd_bufinfo)) {
				/*
				 * Provide all the info we have
				 */
				if (copyout(&kd_bufinfo, where, sizeof(kd_bufinfo)))
					ret = EINVAL;
			} else {
				/*
				 * For backwards compatibility, only provide
				 * as much info as there is room for.
				 */
				if (copyout(&kd_bufinfo, where, size))
					ret = EINVAL;
			}
			break;

		case KERN_KDREADCURTHRMAP:
			ret = kdbg_readcurthrmap(where, sizep);
			break;

		case KERN_KDEFLAGS:
			value &= KDBG_USERFLAGS;
			kd_ctrl_page.kdebug_flags |= value;
			break;

		case KERN_KDDFLAGS:
			value &= KDBG_USERFLAGS;
			kd_ctrl_page.kdebug_flags &= ~value;
			break;

		case KERN_KDENABLE:
			/*
			 * Enable tracing mechanism.  Two types:
			 * KDEBUG_TRACE is the standard one,
			 * and KDEBUG_PPT which is a carefully
			 * chosen subset to avoid performance impact.
			 */
			if (value) {
				/*
				 * enable only if buffer is initialized
				 */
				if (!(kd_ctrl_page.kdebug_flags & KDBG_BUFINIT) || 
				    !(value == KDEBUG_ENABLE_TRACE || value == KDEBUG_ENABLE_PPT)) {
					ret = EINVAL;
					break;
				}
				kdbg_thrmap_init();

				kdbg_set_tracing_enabled(TRUE, value);
			}
			else
			{
				if (!kdebug_enable) {
					break;
				}

				kernel_debug_disable();
			}
			break;

		case KERN_KDSETBUF:
			kdbg_set_nkdbufs(value);
			break;

		case KERN_KDSETUP:
			ret = kdbg_reinit(FALSE);
			break;

		case KERN_KDREMOVE:
			ktrace_reset(KTRACE_KDEBUG);
			break;

		case KERN_KDSETREG:
			if(size < sizeof(kd_regtype)) {
				ret = EINVAL;
				break;
			}
			if (copyin(where, &kd_Reg, sizeof(kd_regtype))) {
				ret = EINVAL;
				break;
			}

			ret = kdbg_setreg(&kd_Reg);
			break;

		case KERN_KDGETREG:
			ret = EINVAL;
			break;

		case KERN_KDREADTR:
			ret = kdbg_read(where, sizep, NULL, NULL, RAW_VERSION1);
			break;

		case KERN_KDWRITETR:
		case KERN_KDWRITETR_V3:
		case KERN_KDWRITEMAP:
		case KERN_KDWRITEMAP_V3:
		{
			struct	vfs_context context;
			struct	fileproc *fp;
			size_t	number;
			vnode_t	vp;
			int	fd;

			if (name[0] == KERN_KDWRITETR || name[0] == KERN_KDWRITETR_V3) {
				(void)kdbg_wait(size, TRUE);
			}
			p = current_proc();
			fd = value;

			proc_fdlock(p);
			if ( (ret = fp_lookup(p, fd, &fp, 1)) ) {
				proc_fdunlock(p);
				break;
			}
			context.vc_thread = current_thread();
			context.vc_ucred = fp->f_fglob->fg_cred;

			if (FILEGLOB_DTYPE(fp->f_fglob) != DTYPE_VNODE) {
				fp_drop(p, fd, fp, 1);
				proc_fdunlock(p);

				ret = EBADF;
				break;
			}
			vp = (struct vnode *)fp->f_fglob->fg_data;
			proc_fdunlock(p);

			if ((ret = vnode_getwithref(vp)) == 0) {
				RAW_file_offset = fp->f_fglob->fg_offset;
				if (name[0] == KERN_KDWRITETR || name[0] == KERN_KDWRITETR_V3) {
					number = nkdbufs * sizeof(kd_buf);

					KDBG_RELEASE(TRACE_WRITING_EVENTS | DBG_FUNC_START);
					if (name[0] == KERN_KDWRITETR_V3)
						ret = kdbg_read(0, &number, vp, &context, RAW_VERSION3);
					else
						ret = kdbg_read(0, &number, vp, &context, RAW_VERSION1);
					KDBG_RELEASE(TRACE_WRITING_EVENTS | DBG_FUNC_END, number);

					*sizep = number;
				} else {
					number = kd_mapcount * sizeof(kd_threadmap);
					if (name[0] == KERN_KDWRITEMAP_V3) {
						ret = kdbg_readthrmap_v3(0, number, fd);
					} else {
						ret = kdbg_write_thread_map(vp, &context);
					}
				}
				fp->f_fglob->fg_offset = RAW_file_offset;
				vnode_put(vp);
			}
			fp_drop(p, fd, fp, 0);

			break;
		}
		case KERN_KDBUFWAIT:
			*sizep = kdbg_wait(size, FALSE);
			break;

		case KERN_KDPIDTR:
			if (size < sizeof(kd_regtype)) {
				ret = EINVAL;
				break;
			}
			if (copyin(where, &kd_Reg, sizeof(kd_regtype))) {
				ret = EINVAL;
				break;
			}

			ret = kdbg_setpid(&kd_Reg);
			break;

		case KERN_KDPIDEX:
			if (size < sizeof(kd_regtype)) {
				ret = EINVAL;
				break;
			}
			if (copyin(where, &kd_Reg, sizeof(kd_regtype))) {
				ret = EINVAL;
				break;
			}

			ret = kdbg_setpidex(&kd_Reg);
			break;

		case KERN_KDCPUMAP:
			ret = kdbg_readcpumap(where, sizep);
			break;

		case KERN_KDTHRMAP:
			ret = kdbg_copyout_thread_map(where, sizep);
			break;

		case KERN_KDSET_TYPEFILTER: {
			ret = kdbg_copyin_typefilter(where, size);
			break;
		}

		case KERN_KDTEST:
			ret = kdbg_test(size);
			break;

		default:
			ret = EINVAL;
			break;
	}
out:
	ktrace_unlock();

	return ret;
}