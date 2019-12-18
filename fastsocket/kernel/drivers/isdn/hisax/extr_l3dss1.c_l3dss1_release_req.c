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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/ * uus1_data; } ;
struct TYPE_4__ {TYPE_1__ dss1; } ;
struct l3_process {int /*<<< orphan*/  timer; TYPE_2__ prot; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_T308_1 ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_RELEASE ; 
 int /*<<< orphan*/  StopAllL3Timer (struct l3_process*) ; 
 int /*<<< orphan*/  T308 ; 
 int /*<<< orphan*/  l3dss1_message (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l3dss1_msg_with_uus (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 

__attribute__((used)) static void
l3dss1_release_req(struct l3_process *pc, u_char pr, void *arg)
{
	StopAllL3Timer(pc);
	newl3state(pc, 19);
	if (!pc->prot.dss1.uus1_data[0]) 
		l3dss1_message(pc, MT_RELEASE);
	else
		l3dss1_msg_with_uus(pc, MT_RELEASE);
	L3AddTimer(&pc->timer, T308, CC_T308_1);
}