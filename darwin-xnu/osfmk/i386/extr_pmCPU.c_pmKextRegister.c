#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pmIPIHandler; int /*<<< orphan*/  (* pmCPUStateInit ) () ;} ;
typedef  TYPE_1__ pmDispatch_t ;
struct TYPE_7__ {int /*<<< orphan*/  DisableApicTimer; int /*<<< orphan*/  InterruptStats; int /*<<< orphan*/  IsInterrupting; int /*<<< orphan*/  InterruptPending; int /*<<< orphan*/  pmSendIPI; int /*<<< orphan*/ * topoParms; int /*<<< orphan*/  timerQueueMigrate; int /*<<< orphan*/  RTCClockAdjust; int /*<<< orphan*/  ThreadGetUrgency; int /*<<< orphan*/  GetNanotimeInfo; int /*<<< orphan*/  GetSavedRunCount; int /*<<< orphan*/  ThreadBind; int /*<<< orphan*/  LCPUtoProcessor; int /*<<< orphan*/  GetHibernate; int /*<<< orphan*/  LockCPUTopology; int /*<<< orphan*/  GetPkgRoot; int /*<<< orphan*/  GetMyPackage; int /*<<< orphan*/  GetMyDie; int /*<<< orphan*/  GetMyCore; int /*<<< orphan*/  GetMyLCPU; int /*<<< orphan*/  GetPackage; int /*<<< orphan*/  GetDie; int /*<<< orphan*/  GetCore; int /*<<< orphan*/  GetLCPU; int /*<<< orphan*/  initComplete; int /*<<< orphan*/  resyncDeadlines; int /*<<< orphan*/  setRTCPop; } ;
typedef  TYPE_2__ pmCallBacks_t ;
typedef  int /*<<< orphan*/  i386_intr_func_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ PM_DISPATCH_VERSION ; 
 scalar_t__ earlyTopology ; 
 int /*<<< orphan*/  lapic_disable_timer ; 
 int /*<<< orphan*/  lapic_interrupt_counts ; 
 int /*<<< orphan*/  lapic_is_interrupt_pending ; 
 int /*<<< orphan*/  lapic_is_interrupting ; 
 int /*<<< orphan*/  lapic_set_pm_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  pmCPUGetHibernate ; 
 TYPE_1__* pmDispatch ; 
 int /*<<< orphan*/  pmGetCore ; 
 int /*<<< orphan*/  pmGetDie ; 
 int /*<<< orphan*/  pmGetLogicalCPU ; 
 int /*<<< orphan*/  pmGetMyCore ; 
 int /*<<< orphan*/  pmGetMyDie ; 
 int /*<<< orphan*/  pmGetMyLogicalCPU ; 
 int /*<<< orphan*/  pmGetMyPackage ; 
 int /*<<< orphan*/  pmGetNanotimeInfo ; 
 int /*<<< orphan*/  pmGetPackage ; 
 int /*<<< orphan*/  pmGetPkgRoot ; 
 int /*<<< orphan*/  pmGetSavedRunCount ; 
 int /*<<< orphan*/  pmInitComplete ; 
 int /*<<< orphan*/  pmLCPUtoProcessor ; 
 int /*<<< orphan*/  pmLockCPUTopology ; 
 int /*<<< orphan*/  pmReSyncDeadlines ; 
 int /*<<< orphan*/  pmSendIPI ; 
 int /*<<< orphan*/  pmThreadGetUrgency ; 
 int /*<<< orphan*/  pmTimerQueueMigrate ; 
 int /*<<< orphan*/  rtc_clock_adjust ; 
 int /*<<< orphan*/  setPop ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  thread_bind ; 
 int /*<<< orphan*/  topoParms ; 

void
pmKextRegister(uint32_t version, pmDispatch_t *cpuFuncs,
    pmCallBacks_t *callbacks)
{
	if (callbacks != NULL && version == PM_DISPATCH_VERSION) {
		callbacks->setRTCPop            = setPop;
		callbacks->resyncDeadlines      = pmReSyncDeadlines;
		callbacks->initComplete         = pmInitComplete;
		callbacks->GetLCPU              = pmGetLogicalCPU;
		callbacks->GetCore              = pmGetCore;
		callbacks->GetDie               = pmGetDie;
		callbacks->GetPackage           = pmGetPackage;
		callbacks->GetMyLCPU            = pmGetMyLogicalCPU;
		callbacks->GetMyCore            = pmGetMyCore;
		callbacks->GetMyDie             = pmGetMyDie;
		callbacks->GetMyPackage         = pmGetMyPackage;
		callbacks->GetPkgRoot           = pmGetPkgRoot;
		callbacks->LockCPUTopology      = pmLockCPUTopology;
		callbacks->GetHibernate         = pmCPUGetHibernate;
		callbacks->LCPUtoProcessor      = pmLCPUtoProcessor;
		callbacks->ThreadBind           = thread_bind;
		callbacks->GetSavedRunCount     = pmGetSavedRunCount;
		callbacks->GetNanotimeInfo	= pmGetNanotimeInfo;
		callbacks->ThreadGetUrgency	= pmThreadGetUrgency;
		callbacks->RTCClockAdjust	= rtc_clock_adjust;
		callbacks->timerQueueMigrate    = pmTimerQueueMigrate;
		callbacks->topoParms            = &topoParms;
		callbacks->pmSendIPI		= pmSendIPI;
		callbacks->InterruptPending	= lapic_is_interrupt_pending;
		callbacks->IsInterrupting	= lapic_is_interrupting;
		callbacks->InterruptStats	= lapic_interrupt_counts;
		callbacks->DisableApicTimer	= lapic_disable_timer;
	} else {
		panic("Version mis-match between Kernel and CPU PM");
	}

	if (cpuFuncs != NULL) {
		if (pmDispatch) {
			panic("Attempt to re-register power management interface--AICPM present in xcpm mode? %p->%p", pmDispatch, cpuFuncs);
		}

		pmDispatch = cpuFuncs;

		if (earlyTopology
		    && pmDispatch->pmCPUStateInit != NULL) {
			(*pmDispatch->pmCPUStateInit)();
			earlyTopology = FALSE;
		}

		if (pmDispatch->pmIPIHandler != NULL) {
			lapic_set_pm_func((i386_intr_func_t)pmDispatch->pmIPIHandler);
		}
	}
}