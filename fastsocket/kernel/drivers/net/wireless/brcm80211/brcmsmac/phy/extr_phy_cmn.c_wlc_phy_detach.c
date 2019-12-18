#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcms_phy_pub {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* detach ) (struct brcms_phy*) ;} ;
struct brcms_phy {TYPE_2__ pi_fptr; struct brcms_phy* next; TYPE_1__* sh; int /*<<< orphan*/ * phycal_timer; scalar_t__ refcnt; } ;
struct TYPE_3__ {struct brcms_phy* phy_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct brcms_phy*) ; 
 int /*<<< orphan*/  stub1 (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlapi_free_timer (int /*<<< orphan*/ *) ; 

void wlc_phy_detach(struct brcms_phy_pub *pih)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;

	if (pih) {
		if (--pi->refcnt)
			return;

		if (pi->phycal_timer) {
			wlapi_free_timer(pi->phycal_timer);
			pi->phycal_timer = NULL;
		}

		if (pi->sh->phy_head == pi)
			pi->sh->phy_head = pi->next;
		else if (pi->sh->phy_head->next == pi)
			pi->sh->phy_head->next = NULL;

		if (pi->pi_fptr.detach)
			(pi->pi_fptr.detach)(pi);

		kfree(pi);
	}
}