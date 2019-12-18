#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct bfa_s {int dummy; } ;
struct bfa_lport_cfg_s {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;
struct TYPE_4__ {int /*<<< orphan*/  flogi_sent; } ;
struct TYPE_6__ {struct bfa_lport_cfg_s port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_1__ stats; int /*<<< orphan*/  auth_reqd; int /*<<< orphan*/  lps; TYPE_3__ bport; TYPE_2__* fcs; } ;
struct TYPE_5__ {struct bfa_s* bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcport_get_maxfrsize (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_lps_flogi (int /*<<< orphan*/ ,struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_fabric_login(struct bfa_fcs_fabric_s *fabric)
{
	struct bfa_s		*bfa = fabric->fcs->bfa;
	struct bfa_lport_cfg_s	*pcfg = &fabric->bport.port_cfg;
	u8			alpa = 0;


	bfa_lps_flogi(fabric->lps, fabric, alpa, bfa_fcport_get_maxfrsize(bfa),
		      pcfg->pwwn, pcfg->nwwn, fabric->auth_reqd);

	fabric->stats.flogi_sent++;
}