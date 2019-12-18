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
struct modctl {int /*<<< orphan*/  mod_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_KERNEL_SYMBOLS_NEVER ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  MODCTL_FBT_BLACKLISTED_PROBES_PROVIDED ; 
 int /*<<< orphan*/  MODCTL_FBT_INVALID ; 
 int /*<<< orphan*/  MODCTL_FBT_PRIVATE_PROBES_PROVIDED ; 
 int /*<<< orphan*/  MODCTL_FBT_PROBES_PROVIDED ; 
 int /*<<< orphan*/  MODCTL_FBT_PROVIDE_BLACKLISTED_PROBES ; 
 scalar_t__ MOD_FBT_DONE (struct modctl*) ; 
 scalar_t__ MOD_FBT_PROVIDE_BLACKLISTED_PROBES (struct modctl*) ; 
 scalar_t__ MOD_FBT_PROVIDE_PRIVATE_PROBES (struct modctl*) ; 
 scalar_t__ MOD_HAS_KERNEL_SYMBOLS (struct modctl*) ; 
 scalar_t__ MOD_HAS_USERSPACE_SYMBOLS (struct modctl*) ; 
 scalar_t__ dtrace_kernel_symbol_mode ; 
 scalar_t__ fbt_module_excluded (struct modctl*) ; 
 int /*<<< orphan*/  fbt_provide_module_kernel_syms (struct modctl*) ; 
 int /*<<< orphan*/  fbt_provide_module_user_syms (struct modctl*) ; 
 scalar_t__ ignore_fbt_blacklist ; 
 int /*<<< orphan*/  mod_lock ; 

void
fbt_provide_module(void *arg, struct modctl *ctl)
{
#pragma unused(arg)
	ASSERT(ctl != NULL);
	ASSERT(dtrace_kernel_symbol_mode != DTRACE_KERNEL_SYMBOLS_NEVER);
	LCK_MTX_ASSERT(&mod_lock, LCK_MTX_ASSERT_OWNED);

	// Update the "ignore blacklist" bit
	if (ignore_fbt_blacklist)
		ctl->mod_flags |= MODCTL_FBT_PROVIDE_BLACKLISTED_PROBES;

	if (MOD_FBT_DONE(ctl))
		return;

	if (fbt_module_excluded(ctl)) {
		ctl->mod_flags |= MODCTL_FBT_INVALID;
		return;
	}

	if (MOD_HAS_KERNEL_SYMBOLS(ctl)) {
		fbt_provide_module_kernel_syms(ctl);
		ctl->mod_flags |= MODCTL_FBT_PROBES_PROVIDED;
		if (MOD_FBT_PROVIDE_BLACKLISTED_PROBES(ctl))
			ctl->mod_flags |= MODCTL_FBT_BLACKLISTED_PROBES_PROVIDED;
		return;
	}

	if (MOD_HAS_USERSPACE_SYMBOLS(ctl)) {
		fbt_provide_module_user_syms(ctl);
		ctl->mod_flags |= MODCTL_FBT_PROBES_PROVIDED;
		if (MOD_FBT_PROVIDE_PRIVATE_PROBES(ctl))
			ctl->mod_flags |= MODCTL_FBT_PRIVATE_PROBES_PROVIDED;
		if (MOD_FBT_PROVIDE_BLACKLISTED_PROBES(ctl))
			ctl->mod_flags |= MODCTL_FBT_BLACKLISTED_PROBES_PROVIDED;
		return;
	}
}