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
struct sfb_fcl {int /*<<< orphan*/  fclist; } ;
struct sfb {int dummy; } ;

/* Variables and functions */
 int SFB_BINS ; 
 struct sfb_fcl* SFB_FC_LIST (struct sfb*,int) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfb_fclist_append (struct sfb*,struct sfb_fcl*) ; 

__attribute__((used)) static void
sfb_fclists_clean(struct sfb *sp)
{
	int i;

	/* Move all the flow control entries to the flowadv list */
	for (i = 0; i < SFB_BINS; ++i) {
		struct sfb_fcl *fcl = SFB_FC_LIST(sp, i);
		if (!STAILQ_EMPTY(&fcl->fclist))
			sfb_fclist_append(sp, fcl);
	}
}