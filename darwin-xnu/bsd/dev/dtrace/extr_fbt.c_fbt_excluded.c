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
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  CRITICAL_BLACKLIST_COUNT ; 
 int FALSE ; 
 scalar_t__ LIT_STRNEQL (char const*,char*) ; 
 scalar_t__ LIT_STRNSTART (char const*,char*) ; 
 int /*<<< orphan*/  PROBE_CTX_CLOSURE_COUNT ; 
 int TRUE ; 
 int /*<<< orphan*/  _cmp ; 
 int /*<<< orphan*/ * bsearch (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_blacklist ; 
 scalar_t__ ignore_fbt_blacklist ; 
 int /*<<< orphan*/  probe_ctx_closure ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

int
fbt_excluded(const char* name)
{
	/*
	 * If the user set this, trust they know what they are doing.
	 */
	if (ignore_fbt_blacklist)
		return FALSE;

	if (LIT_STRNSTART(name, "dtrace_") && !LIT_STRNSTART(name, "dtrace_safe_")) {
		/*
		 * Anything beginning with "dtrace_" may be called
		 * from probe context unless it explitly indicates
		 * that it won't be called from probe context by
		 * using the prefix "dtrace_safe_".
		 */
		return TRUE;
	}

	/*
	* Place no probes on critical routines (5221096)
	*/
	if (bsearch( name, critical_blacklist, CRITICAL_BLACKLIST_COUNT, sizeof(name), _cmp ) != NULL)
		return TRUE;

	/*
	* Place no probes that could be hit in probe context.
	*/
	if (bsearch( name, probe_ctx_closure, PROBE_CTX_CLOSURE_COUNT, sizeof(name), _cmp ) != NULL) {
		return TRUE;
	}

	/*
	* Place no probes that could be hit in probe context.
	* In the interests of safety, some of these may be overly cautious.
	* Also exclude very low-level "firmware" class calls.
	*/
	if (LIT_STRNSTART(name, "cpu_") ||	/* Coarse */
		LIT_STRNSTART(name, "platform_") ||	/* Coarse */
		LIT_STRNSTART(name, "machine_") ||	/* Coarse */
		LIT_STRNSTART(name, "ml_") ||	/* Coarse */
		LIT_STRNSTART(name, "PE_") ||	/* Coarse */
		LIT_STRNSTART(name, "rtc_") ||	/* Coarse */
		LIT_STRNSTART(name, "_rtc_") ||
		LIT_STRNSTART(name, "rtclock_") ||
		LIT_STRNSTART(name, "clock_") ||
		LIT_STRNSTART(name, "bcopy") ||
		LIT_STRNSTART(name, "pmap_") ||
		LIT_STRNSTART(name, "hw_") ||	/* Coarse */
		LIT_STRNSTART(name, "lapic_") ||	/* Coarse */
		LIT_STRNSTART(name, "OSAdd") ||
		LIT_STRNSTART(name, "OSBit") ||
		LIT_STRNSTART(name, "OSDecrement") ||
		LIT_STRNSTART(name, "OSIncrement") ||
		LIT_STRNSTART(name, "OSCompareAndSwap") ||
		LIT_STRNSTART(name, "etimer_") ||
		LIT_STRNSTART(name, "dtxnu_kern_") ||
		LIT_STRNSTART(name, "flush_mmu_tlb_"))
		return TRUE;
	/*
	 * Fasttrap inner-workings we can't instrument
	 * on Intel (6230149)
	*/
	if (LIT_STRNSTART(name, "fasttrap_") ||
		LIT_STRNSTART(name, "fuword") ||
		LIT_STRNSTART(name, "suword"))
		return TRUE;

	if (LIT_STRNSTART(name, "_dtrace"))
		return TRUE; /* Shims in dtrace.c */

	if (LIT_STRNSTART(name, "hibernate_"))
		return TRUE;

	/*
	 * Place no probes in the exception handling path
	 */
#if __arm__ || __arm64__
	if (LIT_STRNSTART(name, "fleh_") ||
		LIT_STRNSTART(name, "sleh_") ||
		LIT_STRNSTART(name, "timer_state_event") ||
		LIT_STRNEQL(name, "get_vfp_enabled"))
		return TRUE;

	if (LIT_STRNSTART(name, "_ZNK15OSMetaClassBase8metaCastEPK11OSMetaClass") ||
		LIT_STRNSTART(name, "_ZN15OSMetaClassBase12safeMetaCastEPKS_PK11OSMetaClass") ||
		LIT_STRNSTART(name, "_ZNK11OSMetaClass13checkMetaCastEPK15OSMetaClassBase"))
		return TRUE;
#endif

#ifdef __x86_64__
	if (LIT_STRNSTART(name, "machine_") ||
		LIT_STRNSTART(name, "idt64") ||
		LIT_STRNSTART(name, "ks_") ||
		LIT_STRNSTART(name, "hndl_") ||
		LIT_STRNSTART(name, "_intr_") ||
		LIT_STRNSTART(name, "mapping_") ||
		LIT_STRNSTART(name, "tsc_") ||
		LIT_STRNSTART(name, "pmCPU") ||
		LIT_STRNSTART(name, "pms") ||
		LIT_STRNSTART(name, "usimple_") ||
		LIT_STRNSTART(name, "lck_spin_lock") ||
		LIT_STRNSTART(name, "lck_spin_unlock") ||
		LIT_STRNSTART(name, "absolutetime_to_") ||
		LIT_STRNSTART(name, "commpage_") ||
		LIT_STRNSTART(name, "ml_") ||
		LIT_STRNSTART(name, "PE_") ||
		LIT_STRNSTART(name, "act_machine") ||
		LIT_STRNSTART(name, "acpi_")  ||
		LIT_STRNSTART(name, "pal_")) {
		return TRUE;
	}
	// Don't Steal Mac OS X
	if (LIT_STRNSTART(name, "dsmos_"))
		return TRUE;

#endif

	/*
	* Place no probes that could be hit on the way to the debugger.
	*/
	if (LIT_STRNSTART(name, "kdp_") ||
		LIT_STRNSTART(name, "kdb_") ||
		LIT_STRNSTART(name, "debug_")) {
		return TRUE;
	}

#if KASAN
	if (LIT_STRNSTART(name, "kasan") ||
		LIT_STRNSTART(name, "__kasan") ||
		LIT_STRNSTART(name, "__asan")) {
		return TRUE;
	}
#endif

	/*
	 * Place no probes that could be hit on the way to a panic.
	 */
	if (NULL != strstr(name, "panic_"))
		return TRUE;

	return FALSE;
}