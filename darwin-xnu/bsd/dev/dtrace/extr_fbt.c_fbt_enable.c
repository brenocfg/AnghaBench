#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct modctl {scalar_t__ mod_loadcnt; int /*<<< orphan*/  mod_nenabled; int /*<<< orphan*/  mod_modname; int /*<<< orphan*/  mod_loaded; } ;
typedef  scalar_t__ perfCallback ;
struct TYPE_2__ {scalar_t__ fbtp_loadcnt; scalar_t__ fbtp_currentval; scalar_t__ fbtp_patchval; scalar_t__ fbtp_patchpoint; int /*<<< orphan*/  fbtp_name; struct modctl* fbtp_ctl; struct TYPE_2__* fbtp_next; } ;
typedef  TYPE_1__ fbt_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_NOTE ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_casptr (scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dtrace_membar_consumer () ; 
 scalar_t__ fbt_perfCallback ; 
 scalar_t__ fbt_verbose ; 
 int /*<<< orphan*/  flush_dcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_icache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_fakestack_suspend () ; 
 int /*<<< orphan*/  ml_nofault_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tempDTraceTrapHook ; 

int
fbt_enable(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg,id)
	fbt_probe_t *fbt = parg;
	struct modctl *ctl = NULL;

    for (; fbt != NULL; fbt = fbt->fbtp_next) {

	ctl = fbt->fbtp_ctl;

	if (!ctl->mod_loaded) {
		if (fbt_verbose) {
			cmn_err(CE_NOTE, "fbt is failing for probe %s "
			    "(module %s unloaded)",
			    fbt->fbtp_name, ctl->mod_modname);
		}

		continue;
	}

	/*
	 * Now check that our modctl has the expected load count.  If it
	 * doesn't, this module must have been unloaded and reloaded -- and
	 * we're not going to touch it.
	 */
	if (ctl->mod_loadcnt != fbt->fbtp_loadcnt) {
		if (fbt_verbose) {
			cmn_err(CE_NOTE, "fbt is failing for probe %s "
			    "(module %s reloaded)",
			    fbt->fbtp_name, ctl->mod_modname);
		}

		continue;
	}

	dtrace_casptr(&tempDTraceTrapHook, NULL, fbt_perfCallback);
	if (tempDTraceTrapHook != (perfCallback)fbt_perfCallback) {
		if (fbt_verbose) {
			cmn_err(CE_NOTE, "fbt_enable is failing for probe %s "
			    "in module %s: tempDTraceTrapHook already occupied.",
			    fbt->fbtp_name, ctl->mod_modname);
		}
		continue;
	}

	if (fbt->fbtp_currentval != fbt->fbtp_patchval) {
#if KASAN
		/* Since dtrace probes can call into KASan and vice versa, things can get
		 * very slow if we have a lot of probes. This call will disable the KASan
		 * fakestack after a threshold of probes is reached. */
		kasan_fakestack_suspend();
#endif

		(void)ml_nofault_copy( (vm_offset_t)&fbt->fbtp_patchval, (vm_offset_t)fbt->fbtp_patchpoint,
								sizeof(fbt->fbtp_patchval));
		/*
		 * Make the patched instruction visible via a data + instruction
		 * cache flush for the platforms that need it
		 */
		flush_dcache((vm_offset_t)fbt->fbtp_patchpoint,(vm_size_t)sizeof(fbt->fbtp_patchval), 0);
		invalidate_icache((vm_offset_t)fbt->fbtp_patchpoint,(vm_size_t)sizeof(fbt->fbtp_patchval), 0);
                fbt->fbtp_currentval = fbt->fbtp_patchval;

		ctl->mod_nenabled++;
	}

    }

    dtrace_membar_consumer();

    return (0);
}