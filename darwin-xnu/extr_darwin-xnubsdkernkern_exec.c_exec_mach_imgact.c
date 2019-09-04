#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  uintptr_t uint64_t ;
typedef  int /*<<< orphan*/ * thread_t ;
typedef  int /*<<< orphan*/ * task_t ;
struct uthread {int dummy; } ;
struct mach_header {scalar_t__ magic; scalar_t__ filetype; int cputype; scalar_t__ cpusubtype; } ;
struct image_params {int ip_flags; scalar_t__ ip_origcputype; scalar_t__ ip_origcpusubtype; int ip_csflags; int /*<<< orphan*/ * ip_px_sa; TYPE_22__* ip_vattr; int /*<<< orphan*/ * ip_new_thread; scalar_t__ ip_endargv; scalar_t__ ip_endenvv; int /*<<< orphan*/  ip_envc; scalar_t__ ip_startargv; int /*<<< orphan*/  ip_argc; int /*<<< orphan*/  ip_vfs_context; scalar_t__ ip_vdata; } ;
struct _posix_spawnattr {scalar_t__* psa_binprefs; int psa_flags; } ;
typedef  TYPE_3__* proc_t ;
typedef  TYPE_4__* os_reason_t ;
typedef  scalar_t__ load_return_t ;
struct TYPE_40__ {int csflags; int /*<<< orphan*/ * threadstate; int /*<<< orphan*/  threadstate_sz; int /*<<< orphan*/ * uuid; scalar_t__ platform_binary; int /*<<< orphan*/  all_image_info_size; int /*<<< orphan*/  all_image_info_addr; int /*<<< orphan*/  mach_header; scalar_t__ dynlinker; scalar_t__ unixproc; int /*<<< orphan*/  is_64bit_addr; } ;
typedef  TYPE_5__ load_result_t ;
typedef  scalar_t__ cpu_type_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_39__ {int /*<<< orphan*/  osr_flags; } ;
struct TYPE_38__ {int p_pid; scalar_t__ p_cputype; int p_cpusubtype; int p_csflags; int p_lflag; scalar_t__ p_pptr; int /*<<< orphan*/  p_flag; int /*<<< orphan*/  p_stat; int /*<<< orphan*/ * p_uuid; int /*<<< orphan*/  p_acflag; int /*<<< orphan*/  user_stack; TYPE_2__* p_fd; TYPE_1__* p_rlimit; } ;
struct TYPE_37__ {scalar_t__ fd_rdir; } ;
struct TYPE_36__ {uintptr_t va_fileid; } ;
struct TYPE_35__ {int /*<<< orphan*/  rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFORK ; 
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_PROC_EXITREASON_CREATE ; 
 int CPU_ARCH_ABI64 ; 
 int CPU_SUBTYPE_MASK ; 
 scalar_t__ CPU_TYPE_ANY ; 
 int CS_DATAVAULT_CONTROLLER ; 
 int CS_DEV_CODE ; 
 int CS_DYLD_PLATFORM ; 
 int CS_ENFORCEMENT ; 
 int CS_ENTITLEMENTS_VALIDATED ; 
 int CS_ENTITLEMENT_FLAGS ; 
 int CS_EXEC_INHERIT_SIP ; 
 int CS_EXEC_SET_ENFORCEMENT ; 
 int CS_EXEC_SET_HARD ; 
 int CS_EXEC_SET_KILL ; 
 int CS_FORCED_LV ; 
 int CS_HARD ; 
 int CS_INSTALLER ; 
 int CS_KILL ; 
 int CS_NVRAM_UNRESTRICTED ; 
 int CS_REQUIRE_LV ; 
 int CS_RESTRICT ; 
 int CS_RUNTIME ; 
 int CS_SIGNED ; 
 int CS_VALID ; 
 int /*<<< orphan*/  DBG_BSD_PROC ; 
 int DBG_FUNC_NONE ; 
 int EBADARCH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_ACTV_THREADSTATE ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_APPLE_STRING_INIT ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_BAD_MACHO ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_COPYOUT_DYNLINKER ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_COPYOUT_STRINGS ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_NO32EXEC ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_STACK_ALLOC ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_SUGID_FAILURE ; 
 int /*<<< orphan*/  EXEC_EXIT_REASON_UPX ; 
 int /*<<< orphan*/  FALSE ; 
 int IMGPF_EXEC ; 
 int IMGPF_IS_64BIT_ADDR ; 
 int IMGPF_IS_64BIT_DATA ; 
 int IMGPF_SPAWN ; 
 int IMGPF_VFORK_EXEC ; 
 int /*<<< orphan*/  IPC_VOUCHER_NULL ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST1 (int /*<<< orphan*/ ,long,long,long,long,uintptr_t) ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ LOAD_BADARCH_X86 ; 
 scalar_t__ LOAD_BADMACHO_UPX ; 
 scalar_t__ LOAD_NOSPACE ; 
 scalar_t__ LOAD_SUCCESS ; 
 scalar_t__ MH_CIGAM ; 
 scalar_t__ MH_CIGAM_64 ; 
 scalar_t__ MH_EXECUTE ; 
 scalar_t__ MH_MAGIC ; 
 scalar_t__ MH_MAGIC_64 ; 
 int NBINPREFS ; 
 int /*<<< orphan*/  OSBitOrAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_REASON_EXEC ; 
 int /*<<< orphan*/  OS_REASON_FLAG_CONSISTENT_FAILURE ; 
 int /*<<< orphan*/  OS_REASON_FLAG_GENERATE_CRASH_REPORT ; 
 TYPE_4__* OS_REASON_NULL ; 
 int POSIX_SPAWN_START_SUSPENDED ; 
 int /*<<< orphan*/  P_EXEC ; 
 int P_LPPWAIT ; 
 int P_LTRACED ; 
 size_t RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SSTOP ; 
 int /*<<< orphan*/  TRACE_DATA_EXEC ; 
 int /*<<< orphan*/  TRACE_STRING_EXEC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * VM_MAP_NULL ; 
 int /*<<< orphan*/  _aio_exec (TYPE_3__*) ; 
 scalar_t__ activate_exec_state (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  argv ; 
 int /*<<< orphan*/  assert (int) ; 
 int copyoutptr (int /*<<< orphan*/ ,uintptr_t,int) ; 
 int /*<<< orphan*/  cpu_type () ; 
 scalar_t__ create_unix_stack (int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*) ; 
 scalar_t__ cs_debug ; 
 int /*<<< orphan*/ * current_task () ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  envv ; 
 int exec_add_apple_strings (struct image_params*,TYPE_5__*) ; 
 int exec_copyout_strings (struct image_params*,int /*<<< orphan*/ *) ; 
 int exec_extract_strings (struct image_params*) ; 
 int exec_handle_sugid (struct image_params*) ; 
 int /*<<< orphan*/  exec_prefault_data (TYPE_3__*,struct image_params*,TYPE_5__*) ; 
 int /*<<< orphan*/  execsigs (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdexec (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/ * fork_create_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_task_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_threadtask (int /*<<< orphan*/ *) ; 
 uintptr_t get_va_fsid (TYPE_22__*) ; 
 int /*<<< orphan*/  grade_binary (scalar_t__,int) ; 
 int /*<<< orphan*/  kdbg_trace_string (TYPE_3__*,long*,long*,long*,long*) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ load_machfile (struct image_params*,struct mach_header*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_5__*) ; 
 int load_return_to_errno (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* os_reason_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_reason_free (TYPE_4__*) ; 
 int /*<<< orphan*/  pal_dbg_set_task_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  proc_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  proc_resetregister (TYPE_3__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_3__*) ; 
 int /*<<< orphan*/  psignal (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psignal_vfork (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psignal_vfork_with_reason (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  psignal_with_reason (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  set_proc_name (struct image_params*,TYPE_3__*) ; 
 int /*<<< orphan*/  stopprofclock (TYPE_3__*) ; 
 int /*<<< orphan*/ * swap_task_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_dyld_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_platform_binary (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_suspend_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_terminate_internal (int /*<<< orphan*/ *) ; 
 uintptr_t thread_adjuserstack (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thread_set_mach_voucher (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_setuserstack (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_tid (int /*<<< orphan*/ *) ; 
 TYPE_3__* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_deallocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_map_set_user_wire_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_map_switch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_mach_imgact(struct image_params *imgp)
{
	struct mach_header *mach_header = (struct mach_header *)imgp->ip_vdata;
	proc_t			p = vfs_context_proc(imgp->ip_vfs_context);
	int			error = 0;
	task_t			task;
	task_t			new_task = NULL; /* protected by vfexec */
	thread_t		thread;
	struct uthread		*uthread;
	vm_map_t old_map = VM_MAP_NULL;
	vm_map_t map = VM_MAP_NULL;
	load_return_t		lret;
	load_result_t		load_result = {};
	struct _posix_spawnattr *psa = NULL;
	int			spawn = (imgp->ip_flags & IMGPF_SPAWN);
	int			vfexec = (imgp->ip_flags & IMGPF_VFORK_EXEC);
	int			exec = (imgp->ip_flags & IMGPF_EXEC);
	os_reason_t		exec_failure_reason = OS_REASON_NULL;

	/*
	 * make sure it's a Mach-O 1.0 or Mach-O 2.0 binary; the difference
	 * is a reserved field on the end, so for the most part, we can
	 * treat them as if they were identical. Reverse-endian Mach-O
	 * binaries are recognized but not compatible.
 	 */
	if ((mach_header->magic == MH_CIGAM) ||
	    (mach_header->magic == MH_CIGAM_64)) {
		error = EBADARCH;
		goto bad;
	}

	if ((mach_header->magic != MH_MAGIC) &&
	    (mach_header->magic != MH_MAGIC_64)) {
		error = -1;
		goto bad;
	}

	if (mach_header->filetype != MH_EXECUTE) {
		error = -1;
		goto bad;
	}

	if (imgp->ip_origcputype != 0) {
		/* Fat header previously had an idea about this thin file */
		if (imgp->ip_origcputype != mach_header->cputype ||
			imgp->ip_origcpusubtype != mach_header->cpusubtype) {
			error = EBADARCH;
			goto bad;
		}
	} else {
		imgp->ip_origcputype = mach_header->cputype;
		imgp->ip_origcpusubtype = mach_header->cpusubtype;
	}

	task = current_task();
	thread = current_thread();
	uthread = get_bsdthread_info(thread);

	if ((mach_header->cputype & CPU_ARCH_ABI64) == CPU_ARCH_ABI64) {
		imgp->ip_flags |= IMGPF_IS_64BIT_ADDR | IMGPF_IS_64BIT_DATA;
	}

	/* If posix_spawn binprefs exist, respect those prefs. */
	psa = (struct _posix_spawnattr *) imgp->ip_px_sa;
	if (psa != NULL && psa->psa_binprefs[0] != 0) {
		int pr = 0;
		for (pr = 0; pr < NBINPREFS; pr++) {
			cpu_type_t pref = psa->psa_binprefs[pr];
			if (pref == 0) {
				/* No suitable arch in the pref list */
				error = EBADARCH;
				goto bad;
			}

			if (pref == CPU_TYPE_ANY) {
				/* Jump to regular grading */
				goto grade;
			}

			if (pref == imgp->ip_origcputype) {
				/* We have a match! */
				goto grade;
			}
		}
		error = EBADARCH;
		goto bad;
	}
grade:
	if (!grade_binary(imgp->ip_origcputype, imgp->ip_origcpusubtype & ~CPU_SUBTYPE_MASK)) {
		error = EBADARCH;
		goto bad;
	}



	/* Copy in arguments/environment from the old process */
	error = exec_extract_strings(imgp);
	if (error)
		goto bad;

	AUDIT_ARG(argv, imgp->ip_startargv, imgp->ip_argc, 
	    imgp->ip_endargv - imgp->ip_startargv);
	AUDIT_ARG(envv, imgp->ip_endargv, imgp->ip_envc,
	    imgp->ip_endenvv - imgp->ip_endargv);

	/*
	 * We are being called to activate an image subsequent to a vfork()
	 * operation; in this case, we know that our task, thread, and
	 * uthread are actually those of our parent, and our proc, which we
	 * obtained indirectly from the image_params vfs_context_t, is the
	 * new child process.
	 */
	if (vfexec) {
		imgp->ip_new_thread = fork_create_child(task,
												NULL,
												p,
												FALSE,
												(imgp->ip_flags & IMGPF_IS_64BIT_ADDR),
												(imgp->ip_flags & IMGPF_IS_64BIT_DATA),
												FALSE);
		/* task and thread ref returned, will be released in __mac_execve */
		if (imgp->ip_new_thread == NULL) {
			error = ENOMEM;
			goto bad;
		}
	}


	/* reset local idea of thread, uthread, task */
	thread = imgp->ip_new_thread;
	uthread = get_bsdthread_info(thread);
	task = new_task = get_threadtask(thread);

	/*
	 *	Load the Mach-O file.
	 *
	 * NOTE: An error after this point  indicates we have potentially
	 * destroyed or overwritten some process state while attempting an
	 * execve() following a vfork(), which is an unrecoverable condition.
	 * We send the new process an immediate SIGKILL to avoid it executing
	 * any instructions in the mutated address space. For true spawns,
	 * this is not the case, and "too late" is still not too late to
	 * return an error code to the parent process.
	 */

	/*
	 * Actually load the image file we previously decided to load.
	 */
	lret = load_machfile(imgp, mach_header, thread, &map, &load_result);
	if (lret != LOAD_SUCCESS) {
		error = load_return_to_errno(lret);

		KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
						p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_BAD_MACHO, 0, 0);
		if (lret == LOAD_BADMACHO_UPX) {
			/* set anything that might be useful in the crash report */
			set_proc_name(imgp, p);

			exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_UPX);
			exec_failure_reason->osr_flags |= OS_REASON_FLAG_GENERATE_CRASH_REPORT;
			exec_failure_reason->osr_flags |= OS_REASON_FLAG_CONSISTENT_FAILURE;
		} else if (lret == LOAD_BADARCH_X86) {
			/* set anything that might be useful in the crash report */
			set_proc_name(imgp, p);

			exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_NO32EXEC);
			exec_failure_reason->osr_flags |= OS_REASON_FLAG_GENERATE_CRASH_REPORT;
			exec_failure_reason->osr_flags |= OS_REASON_FLAG_CONSISTENT_FAILURE;
		} else {
			exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_BAD_MACHO);
		}

		goto badtoolate;
	}

	proc_lock(p);
	p->p_cputype = imgp->ip_origcputype;
	p->p_cpusubtype = imgp->ip_origcpusubtype;
	proc_unlock(p);

	vm_map_set_user_wire_limit(map, p->p_rlimit[RLIMIT_MEMLOCK].rlim_cur);

	/* 
	 * Set code-signing flags if this binary is signed, or if parent has
	 * requested them on exec.
	 */
	if (load_result.csflags & CS_VALID) {
		imgp->ip_csflags |= load_result.csflags & 
			(CS_VALID|CS_SIGNED|CS_DEV_CODE|
			 CS_HARD|CS_KILL|CS_RESTRICT|CS_ENFORCEMENT|CS_REQUIRE_LV|
			 CS_FORCED_LV|CS_ENTITLEMENTS_VALIDATED|CS_DYLD_PLATFORM|CS_RUNTIME|
			 CS_ENTITLEMENT_FLAGS|
			 CS_EXEC_SET_HARD|CS_EXEC_SET_KILL|CS_EXEC_SET_ENFORCEMENT);
	} else {
		imgp->ip_csflags &= ~CS_VALID;
	}

	if (p->p_csflags & CS_EXEC_SET_HARD)
		imgp->ip_csflags |= CS_HARD;
	if (p->p_csflags & CS_EXEC_SET_KILL)
		imgp->ip_csflags |= CS_KILL;
	if (p->p_csflags & CS_EXEC_SET_ENFORCEMENT)
		imgp->ip_csflags |= CS_ENFORCEMENT;
	if (p->p_csflags & CS_EXEC_INHERIT_SIP) {
		if (p->p_csflags & CS_INSTALLER)
			imgp->ip_csflags |= CS_INSTALLER;
		if (p->p_csflags & CS_DATAVAULT_CONTROLLER)
			imgp->ip_csflags |= CS_DATAVAULT_CONTROLLER;
		if (p->p_csflags & CS_NVRAM_UNRESTRICTED)
			imgp->ip_csflags |= CS_NVRAM_UNRESTRICTED;
	}

	/*
	 * Set up the system reserved areas in the new address space.
	 */
	int cpu_subtype;
	cpu_subtype = 0; /* all cpu_subtypes use the same shared region */
	vm_map_exec(map, task, load_result.is_64bit_addr, (void *)p->p_fd->fd_rdir, cpu_type(), cpu_subtype);

	/*
	 * Close file descriptors which specify close-on-exec.
	 */
	fdexec(p, psa != NULL ? psa->psa_flags : 0, exec);

	/*
	 * deal with set[ug]id.
	 */
	error = exec_handle_sugid(imgp);
	if (error) {
		vm_map_deallocate(map);

		KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
						p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_SUGID_FAILURE, 0, 0);
		exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_SUGID_FAILURE);
		goto badtoolate;
	}

	/*
	 * Commit to new map.
	 *
	 * Swap the new map for the old for target task, which consumes
	 * our new map reference but each leaves us responsible for the
	 * old_map reference.  That lets us get off the pmap associated
	 * with it, and then we can release it.
	 *
	 * The map needs to be set on the target task which is different
	 * than current task, thus swap_task_map is used instead of
	 * vm_map_switch.
	 */
	old_map = swap_task_map(task, thread, map);
	vm_map_deallocate(old_map);
	old_map = NULL;

	lret = activate_exec_state(task, p, thread, &load_result);
	if (lret != KERN_SUCCESS) {

		KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
						p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_ACTV_THREADSTATE, 0, 0);
		exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_ACTV_THREADSTATE);
		goto badtoolate;
	}

	/*
	 * deal with voucher on exec-calling thread.
	 */
	if (imgp->ip_new_thread == NULL)
		thread_set_mach_voucher(current_thread(), IPC_VOUCHER_NULL);

	/* Make sure we won't interrupt ourself signalling a partial process */
	if (!vfexec && !spawn && (p->p_lflag & P_LTRACED))
		psignal(p, SIGTRAP);

	if (load_result.unixproc &&
		create_unix_stack(get_task_map(task),
				  &load_result,
				  p) != KERN_SUCCESS) {
		error = load_return_to_errno(LOAD_NOSPACE);

		KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
						p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_STACK_ALLOC, 0, 0);
		exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_STACK_ALLOC);
		goto badtoolate;
	}

	error = exec_add_apple_strings(imgp, &load_result);
	if (error) {

		KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
						p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_APPLE_STRING_INIT, 0, 0);
		exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_APPLE_STRING_INIT);
		goto badtoolate;
	}

	/* Switch to target task's map to copy out strings */
	old_map = vm_map_switch(get_task_map(task));

	if (load_result.unixproc) {
		user_addr_t	ap;

		/*
		 * Copy the strings area out into the new process address
		 * space.
		 */
		ap = p->user_stack;
		error = exec_copyout_strings(imgp, &ap);
		if (error) {
			vm_map_switch(old_map);

			KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
						p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_COPYOUT_STRINGS, 0, 0);
			exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_COPYOUT_STRINGS);
			goto badtoolate;
		}
		/* Set the stack */
		thread_setuserstack(thread, ap);
	}

	if (load_result.dynlinker) {
		uint64_t	ap;
		int			new_ptr_size = (imgp->ip_flags & IMGPF_IS_64BIT_ADDR) ? 8 : 4;

		/* Adjust the stack */
		ap = thread_adjuserstack(thread, -new_ptr_size);
		error = copyoutptr(load_result.mach_header, ap, new_ptr_size);

		if (error) {
			vm_map_switch(old_map);

			KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
						p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_COPYOUT_DYNLINKER, 0, 0);
			exec_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_COPYOUT_DYNLINKER);
			goto badtoolate;
		}
		task_set_dyld_info(task, load_result.all_image_info_addr,
		    load_result.all_image_info_size);
	}

	/* Avoid immediate VM faults back into kernel */
	exec_prefault_data(p, imgp, &load_result);

	vm_map_switch(old_map);

	/* Stop profiling */
	stopprofclock(p);

	/*
	 * Reset signal state.
	 */
	execsigs(p, thread);

	/*
	 * need to cancel async IO requests that can be cancelled and wait for those
	 * already active.  MAY BLOCK!
	 */
	_aio_exec( p );

#if SYSV_SHM
	/* FIXME: Till vmspace inherit is fixed: */
	if (!vfexec && p->vm_shm)
		shmexec(p);
#endif
#if SYSV_SEM
	/* Clean up the semaphores */
	semexit(p);
#endif

	/*
	 * Remember file name for accounting.
	 */
	p->p_acflag &= ~AFORK;

	set_proc_name(imgp, p);

#if CONFIG_SECLUDED_MEMORY
	if (secluded_for_apps &&
	    load_result.platform_binary) {
		if (strncmp(p->p_name,
			    "Camera",
			    sizeof (p->p_name)) == 0) {
			task_set_could_use_secluded_mem(task, TRUE);
		} else {
			task_set_could_use_secluded_mem(task, FALSE);
		}
		if (strncmp(p->p_name,
			    "mediaserverd",
			    sizeof (p->p_name)) == 0) {
			task_set_could_also_use_secluded_mem(task, TRUE);
		}
	}
#endif /* CONFIG_SECLUDED_MEMORY */

#if __arm64__
	if (load_result.legacy_footprint) {
		task_set_legacy_footprint(task, TRUE);
	}
#endif /* __arm64__ */

	pal_dbg_set_task_name(task);

	/*
	 * The load result will have already been munged by AMFI to include the
	 * platform binary flag if boot-args dictated it (AMFI will mark anything
	 * that doesn't go through the upcall path as a platform binary if its
	 * enforcement is disabled).
	 */
	if (load_result.platform_binary) {
		if (cs_debug) {
			printf("setting platform binary on task: pid = %d\n", p->p_pid);
		}

		/*
		 * We must use 'task' here because the proc's task has not yet been
		 * switched to the new one.
		 */
		task_set_platform_binary(task, TRUE);
	} else {
		if (cs_debug) {
			printf("clearing platform binary on task: pid = %d\n", p->p_pid);
		}

		task_set_platform_binary(task, FALSE);
	}

#if DEVELOPMENT || DEBUG
	/*
	 * Update the pid an proc name for importance base if any
	 */
	task_importance_update_owner_info(task);
#endif

	memcpy(&p->p_uuid[0], &load_result.uuid[0], sizeof(p->p_uuid));

#if CONFIG_DTRACE
	dtrace_proc_exec(p);
#endif

	if (kdebug_enable) {
		long args[4] = {};

		uintptr_t fsid = 0, fileid = 0;
		if (imgp->ip_vattr) {
			uint64_t fsid64 = get_va_fsid(imgp->ip_vattr);
			fsid   = fsid64;
			fileid = imgp->ip_vattr->va_fileid;
			// check for (unexpected) overflow and trace zero in that case
			if (fsid != fsid64 || fileid != imgp->ip_vattr->va_fileid) {
				fsid = fileid = 0;
			}
		}
		KERNEL_DEBUG_CONSTANT_IST1(TRACE_DATA_EXEC, p->p_pid, fsid, fileid, 0,
				(uintptr_t)thread_tid(thread));

		/*
		 * Collect the pathname for tracing
		 */
		kdbg_trace_string(p, &args[0], &args[1], &args[2], &args[3]);
		KERNEL_DEBUG_CONSTANT_IST1(TRACE_STRING_EXEC, args[0], args[1],
				args[2], args[3], (uintptr_t)thread_tid(thread));
	}

	/*
	 * If posix_spawned with the START_SUSPENDED flag, stop the
	 * process before it runs.
	 */
	if (imgp->ip_px_sa != NULL) {
		psa = (struct _posix_spawnattr *) imgp->ip_px_sa;
		if (psa->psa_flags & POSIX_SPAWN_START_SUSPENDED) {
			proc_lock(p);
			p->p_stat = SSTOP;
			proc_unlock(p);
			(void) task_suspend_internal(task);
		}
	}

	/*
	 * mark as execed, wakeup the process that vforked (if any) and tell
	 * it that it now has its own resources back
	 */
	OSBitOrAtomic(P_EXEC, &p->p_flag);
	proc_resetregister(p);
	if (p->p_pptr && (p->p_lflag & P_LPPWAIT)) {
		proc_lock(p);
		p->p_lflag &= ~P_LPPWAIT;
		proc_unlock(p);
		wakeup((caddr_t)p->p_pptr);
	}

	/*
	 * Pay for our earlier safety; deliver the delayed signals from
	 * the incomplete vfexec process now that it's complete.
	 */
	if (vfexec && (p->p_lflag & P_LTRACED)) {
		psignal_vfork(p, new_task, thread, SIGTRAP);
	}

	goto done;

badtoolate:
	/* Don't allow child process to execute any instructions */
	if (!spawn) {
		if (vfexec) {
			assert(exec_failure_reason != OS_REASON_NULL);
			psignal_vfork_with_reason(p, new_task, thread, SIGKILL, exec_failure_reason);
			exec_failure_reason = OS_REASON_NULL;
		} else {
			assert(exec_failure_reason != OS_REASON_NULL);
			psignal_with_reason(p, SIGKILL, exec_failure_reason);
			exec_failure_reason = OS_REASON_NULL;

			if (exec) {
				/* Terminate the exec copy task */
				task_terminate_internal(task);
			}
		}

		/* We can't stop this system call at this point, so just pretend we succeeded */
		error = 0;
	} else {
		os_reason_free(exec_failure_reason);
		exec_failure_reason = OS_REASON_NULL;
	}
	
done:
	if (load_result.threadstate) {
		kfree(load_result.threadstate, load_result.threadstate_sz);
		load_result.threadstate = NULL;
	}

bad:
	/* If we hit this, we likely would have leaked an exit reason */
	assert(exec_failure_reason == OS_REASON_NULL);
	return(error);
}