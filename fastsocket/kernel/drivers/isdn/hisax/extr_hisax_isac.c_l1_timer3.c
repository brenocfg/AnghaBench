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
struct isac {int dummy; } ;
struct FsmInst {struct isac* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_L1L2 (struct isac*,int,int /*<<< orphan*/ *) ; 
 int INDICATION ; 
 int /*<<< orphan*/  ISAC_CMD_DI ; 
 int PH_DEACTIVATE ; 
 int /*<<< orphan*/  ph_command (struct isac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l1_timer3(struct FsmInst *fi, int event, void *arg)
{
	struct isac *isac = fi->userdata;

	ph_command(isac, ISAC_CMD_DI);
	D_L1L2(isac, PH_DEACTIVATE | INDICATION, NULL);
}