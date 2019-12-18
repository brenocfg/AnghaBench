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
struct modctl {int /*<<< orphan*/ * mod_user_symbols; struct modctl* mod_next; struct modctl* mod_stale; } ;
typedef  struct modctl modctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 struct modctl* dtrace_modctl_list ; 
 int /*<<< orphan*/  kmem_free (struct modctl*,int) ; 
 int /*<<< orphan*/  mod_lock ; 

__attribute__((used)) static void
dtrace_modctl_remove(struct modctl * ctl)
{
	ASSERT(ctl != NULL);
	LCK_MTX_ASSERT(&mod_lock, LCK_MTX_ASSERT_OWNED);
	modctl_t *prevp, *nextp, *curp;

	// Remove stale chain first
	for (curp=ctl->mod_stale; curp != NULL; curp=nextp) {
		nextp = curp->mod_stale;
		/* There should NEVER be user symbols allocated at this point */
		ASSERT(curp->mod_user_symbols == NULL);	
		kmem_free(curp, sizeof(modctl_t));
	}

	prevp = NULL;
	curp = dtrace_modctl_list;
	
	while (curp != ctl) {
		prevp = curp;
		curp = curp->mod_next;
	}

	if (prevp != NULL) {
		prevp->mod_next = ctl->mod_next;
	}
	else {
		dtrace_modctl_list = ctl->mod_next;
	}

	/* There should NEVER be user symbols allocated at this point */
	ASSERT(ctl->mod_user_symbols == NULL);

	kmem_free (ctl, sizeof(modctl_t));
}