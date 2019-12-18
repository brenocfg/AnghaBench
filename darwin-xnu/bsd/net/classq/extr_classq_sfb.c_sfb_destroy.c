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
struct sfb {struct sfb* sfb_fc_lists; struct sfb* sfb_bins; } ;

/* Variables and functions */
 int /*<<< orphan*/  sfb_bins_zone ; 
 int /*<<< orphan*/  sfb_fcl_zone ; 
 int /*<<< orphan*/  sfb_fclists_clean (struct sfb*) ; 
 int /*<<< orphan*/  sfb_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct sfb*) ; 

void
sfb_destroy(struct sfb *sp)
{
	sfb_fclists_clean(sp);
	if (sp->sfb_bins != NULL) {
		zfree(sfb_bins_zone, sp->sfb_bins);
		sp->sfb_bins = NULL;
	}
	if (sp->sfb_fc_lists != NULL) {
		zfree(sfb_fcl_zone, sp->sfb_fc_lists);
		sp->sfb_fc_lists = NULL;
	}
	zfree(sfb_zone, sp);
}