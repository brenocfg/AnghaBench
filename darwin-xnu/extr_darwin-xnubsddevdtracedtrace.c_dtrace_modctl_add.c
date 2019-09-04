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
struct modctl {struct modctl* mod_next; struct modctl* mod_stale; int /*<<< orphan*/  mod_modname; scalar_t__ mod_loaded; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KMOD_MAX_NAME ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 struct modctl* dtrace_modctl_list ; 
 int /*<<< orphan*/  mod_lock ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_modctl_add(struct modctl * newctl)
{
	struct modctl *nextp, *prevp;

	ASSERT(newctl != NULL);
	LCK_MTX_ASSERT(&mod_lock, LCK_MTX_ASSERT_OWNED);

	// Insert new module at the front of the list,
	
	newctl->mod_next = dtrace_modctl_list;
	dtrace_modctl_list = newctl;

	/*
	 * If a module exists with the same name, then that module
	 * must have been unloaded with enabled probes. We will move
	 * the unloaded module to the new module's stale chain and
	 * then stop traversing the list.
	 */

	prevp = newctl;
	nextp = newctl->mod_next;
    
	while (nextp != NULL) {
		if (nextp->mod_loaded) {
			/* This is a loaded module. Keep traversing. */
			prevp = nextp;
			nextp = nextp->mod_next;
			continue;
		}
		else {
			/* Found an unloaded module */
			if (strncmp (newctl->mod_modname, nextp->mod_modname, KMOD_MAX_NAME)) {
				/* Names don't match. Keep traversing. */
				prevp = nextp;
				nextp = nextp->mod_next;
				continue;
			}
			else {
				/* We found a stale entry, move it. We're done. */
				prevp->mod_next = nextp->mod_next;
				newctl->mod_stale = nextp;
				nextp->mod_next = NULL;
				break;
			}
		}
	}
}