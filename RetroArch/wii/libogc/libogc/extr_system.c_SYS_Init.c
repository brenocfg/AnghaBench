#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  alarm_st ;

/* Variables and functions */
 int /*<<< orphan*/  DisableWriteGatherPipe () ; 
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PI_RSW ; 
 int /*<<< orphan*/  IRQ_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERNEL_HEAP ; 
 int /*<<< orphan*/  LWP_MAX_WATCHDOGS ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _V_EXPORTNAME () ; 
 int /*<<< orphan*/  __IPC_ClntInit () ; 
 int /*<<< orphan*/  __MaskIrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __RSWHandler ; 
 int /*<<< orphan*/  __SYS_InitCallbacks () ; 
 int /*<<< orphan*/  __SYS_PreInit () ; 
 int /*<<< orphan*/  __SYS_SetBootTime () ; 
 int /*<<< orphan*/  __decrementer_init () ; 
 int /*<<< orphan*/  __dsp_bootstrap () ; 
 int /*<<< orphan*/  __exception_init () ; 
 int /*<<< orphan*/  __exi_init () ; 
 int /*<<< orphan*/  __init_syscall_array () ; 
 int /*<<< orphan*/  __ipcbuffer_init () ; 
 int /*<<< orphan*/  __irq_init () ; 
 int /*<<< orphan*/  __libc_init (int) ; 
 int /*<<< orphan*/  __lowmem_init () ; 
 int /*<<< orphan*/  __lwp_cond_init () ; 
 int /*<<< orphan*/  __lwp_mqbox_init () ; 
 int /*<<< orphan*/  __lwp_mutex_init () ; 
 int /*<<< orphan*/  __lwp_objmgr_initinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __lwp_priority_init () ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_sema_init () ; 
 int /*<<< orphan*/  __lwp_sysinit () ; 
 int /*<<< orphan*/  __lwp_thread_coreinit () ; 
 int /*<<< orphan*/  __lwp_thread_startmultitasking () ; 
 int /*<<< orphan*/  __lwp_watchdog_init () ; 
 int /*<<< orphan*/  __lwp_wkspace_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __memlock_init () ; 
 int /*<<< orphan*/  __memprotect_init () ; 
 int /*<<< orphan*/  __si_init () ; 
 int /*<<< orphan*/  __sram_init () ; 
 int /*<<< orphan*/  __sys_inIPL ; 
 int /*<<< orphan*/  __sys_state_init () ; 
 int /*<<< orphan*/  __systemcall_init () ; 
 int /*<<< orphan*/  __timesystem_init () ; 
 int /*<<< orphan*/  sys_alarm_objects ; 
 int /*<<< orphan*/  sys_reset_func_queue ; 
 int system_initialized ; 

void SYS_Init()
{
	u32 level;

	_CPU_ISR_Disable(level);

	__SYS_PreInit();

	if(system_initialized) return;
	system_initialized = 1;

	_V_EXPORTNAME();

	__init_syscall_array();
	__lowmem_init();
#if defined(HW_RVL)
	__ipcbuffer_init();
#endif
	__lwp_wkspace_init(KERNEL_HEAP);
	__lwp_queue_init_empty(&sys_reset_func_queue);
	__lwp_objmgr_initinfo(&sys_alarm_objects,LWP_MAX_WATCHDOGS,sizeof(alarm_st));
	__sys_state_init();
	__lwp_priority_init();
	__lwp_watchdog_init();
	__exception_init();
	__systemcall_init();
	__decrementer_init();
	__irq_init();
	__exi_init();
	__sram_init();
	__si_init();
	__lwp_thread_coreinit();
	__lwp_sysinit();
	__memlock_init();
	__lwp_mqbox_init();
	__lwp_sema_init();
	__lwp_mutex_init();
	__lwp_cond_init();
	__timesystem_init();
	__dsp_bootstrap();

	if(!__sys_inIPL)
		__memprotect_init();

#ifdef SDLOADER_FIX
	__SYS_SetBootTime();
#endif
	DisableWriteGatherPipe();
	__SYS_InitCallbacks();
#if defined(HW_RVL)
	__IPC_ClntInit();
#elif defined(HW_DOL)
	IRQ_Request(IRQ_PI_RSW,__RSWHandler,NULL);
	__MaskIrq(IRQMASK(IRQ_PI_RSW));
#endif
	__libc_init(1);
	__lwp_thread_startmultitasking();
	_CPU_ISR_Restore(level);
}