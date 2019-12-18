#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ etv; } ;
struct TYPE_7__ {scalar_t__ net_id; scalar_t__ etr_id; scalar_t__ etr_pn; } ;
struct TYPE_5__ {scalar_t__ e0; scalar_t__ e1; } ;
struct TYPE_6__ {int psc1; int psc0; TYPE_1__ eacr; } ;
struct etr_aib {TYPE_4__ edf2; TYPE_3__ edf1; TYPE_2__ esw; } ;

/* Variables and functions */
 int etr_lpsc_operational_step ; 
 int etr_lpsc_pps_mode ; 
 int /*<<< orphan*/  etr_port_valid (struct etr_aib*,int) ; 

__attribute__((used)) static int etr_aib_follows(struct etr_aib *a1, struct etr_aib *a2, int p)
{
	int state_a1, state_a2;

	/* Paranoia check: e0/e1 should better be the same. */
	if (a1->esw.eacr.e0 != a2->esw.eacr.e0 ||
	    a1->esw.eacr.e1 != a2->esw.eacr.e1)
		return 0;

	/* Still connected to the same etr ? */
	state_a1 = p ? a1->esw.psc1 : a1->esw.psc0;
	state_a2 = p ? a2->esw.psc1 : a2->esw.psc0;
	if (state_a1 == etr_lpsc_operational_step) {
		if (state_a2 != etr_lpsc_operational_step ||
		    a1->edf1.net_id != a2->edf1.net_id ||
		    a1->edf1.etr_id != a2->edf1.etr_id ||
		    a1->edf1.etr_pn != a2->edf1.etr_pn)
			return 0;
	} else if (state_a2 != etr_lpsc_pps_mode)
		return 0;

	/* The ETV value of a2 needs to be ETV of a1 + 1. */
	if (a1->edf2.etv + 1 != a2->edf2.etv)
		return 0;

	if (!etr_port_valid(a2, p))
		return 0;

	return 1;
}