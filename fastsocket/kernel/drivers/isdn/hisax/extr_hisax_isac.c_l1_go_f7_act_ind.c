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
struct isac {int /*<<< orphan*/  timer; } ;
struct FsmInst {struct isac* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_L1L2 (struct isac*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FsmChangeState (struct FsmInst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FsmDelTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INDICATION ; 
 int /*<<< orphan*/  ISAC_CMD_AR8 ; 
 int PH_ACTIVATE ; 
 int /*<<< orphan*/  ST_L1_F7 ; 
 int /*<<< orphan*/  ph_command (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l1_go_f7_act_ind(struct FsmInst *fi, int event, void *arg)
{
	struct isac *isac = fi->userdata;

	FsmDelTimer(&isac->timer, 0);
	FsmChangeState(fi, ST_L1_F7);
	ph_command(isac, ISAC_CMD_AR8);
	D_L1L2(isac, PH_ACTIVATE | INDICATION, NULL);
}