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
struct modctl {scalar_t__ mod_loadcnt; int /*<<< orphan*/  mod_modname; int /*<<< orphan*/  mod_loaded; int /*<<< orphan*/  mod_nenabled; } ;
struct TYPE_2__ {scalar_t__ sdp_loadcnt; struct TYPE_2__* sdp_next; scalar_t__ sdp_patchpoint; int /*<<< orphan*/  sdp_patchval; int /*<<< orphan*/  sdp_name; struct modctl* sdp_ctl; } ;
typedef  TYPE_1__ sdt_probe_t ;
typedef  scalar_t__ perfCallback ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_NOTE ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_casptr (scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fbt_perfCallback ; 
 int /*<<< orphan*/  flush_dcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_icache (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_nofault_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sdt_verbose ; 
 scalar_t__ tempDTraceTrapHook ; 

__attribute__((used)) static int
sdt_enable(void *arg, dtrace_id_t id, void *parg)
{
#pragma unused(arg,id)
	sdt_probe_t *sdp = parg;
	struct modctl *ctl = sdp->sdp_ctl;

	ctl->mod_nenabled++;

	/*
	 * If this module has disappeared since we discovered its probes,
	 * refuse to enable it.
	 */
	if (!ctl->mod_loaded) {
		if (sdt_verbose) {
			cmn_err(CE_NOTE, "sdt is failing for probe %s "
			    "(module %s unloaded)",
			    sdp->sdp_name, ctl->mod_modname);
		}
		goto err;
	}

	/*
	 * Now check that our modctl has the expected load count.  If it
	 * doesn't, this module must have been unloaded and reloaded -- and
	 * we're not going to touch it.
	 */
	if (ctl->mod_loadcnt != sdp->sdp_loadcnt) {
		if (sdt_verbose) {
			cmn_err(CE_NOTE, "sdt is failing for probe %s "
			    "(module %s reloaded)",
			    sdp->sdp_name, ctl->mod_modname);
		}
		goto err;
	}

	dtrace_casptr(&tempDTraceTrapHook, NULL, fbt_perfCallback);
	if (tempDTraceTrapHook != (perfCallback)fbt_perfCallback) {
		if (sdt_verbose) {
			cmn_err(CE_NOTE, "sdt_enable is failing for probe %s "
			    "in module %s: tempDTraceTrapHook already occupied.",
			    sdp->sdp_name, ctl->mod_modname);
		}
		return (0);
	}

	while (sdp != NULL) {
		(void)ml_nofault_copy( (vm_offset_t)&sdp->sdp_patchval, (vm_offset_t)sdp->sdp_patchpoint, 
		                       (vm_size_t)sizeof(sdp->sdp_patchval));

		/*
		 * Make the patched instruction visible via a data + instruction
		 * cache fush on platforms that need it
		 */
		flush_dcache((vm_offset_t)sdp->sdp_patchpoint,(vm_size_t)sizeof(sdp->sdp_patchval), 0);
		invalidate_icache((vm_offset_t)sdp->sdp_patchpoint,(vm_size_t)sizeof(sdp->sdp_patchval), 0);

		sdp = sdp->sdp_next;
	}

err:
	return (0);
}