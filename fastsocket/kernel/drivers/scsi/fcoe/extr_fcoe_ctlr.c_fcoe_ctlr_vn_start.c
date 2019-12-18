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
struct fcoe_ctlr {TYPE_1__* lp; int /*<<< orphan*/  rnd_state; scalar_t__ probe_tries; } ;
struct TYPE_2__ {int /*<<< orphan*/  wwpn; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcoe_ctlr_vn_restart (struct fcoe_ctlr*) ; 
 int /*<<< orphan*/  prandom32_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcoe_ctlr_vn_start(struct fcoe_ctlr *fip)
{
	fip->probe_tries = 0;
	prandom32_seed(&fip->rnd_state, fip->lp->wwpn);
	fcoe_ctlr_vn_restart(fip);
}