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
typedef  int /*<<< orphan*/  u_char ;
struct l3_process {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_T308_1 ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_N1_REL ; 
 int /*<<< orphan*/  PROTO_DIS_N1 ; 
 int /*<<< orphan*/  StopAllL3Timer (struct l3_process*) ; 
 int /*<<< orphan*/  T308 ; 
 int /*<<< orphan*/  l3_1TR6_message (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 

__attribute__((used)) static void
l3_1tr6_release_req(struct l3_process *pc, u_char pr, void *arg)
{
	StopAllL3Timer(pc);
	newl3state(pc, 19);
	l3_1TR6_message(pc, MT_N1_REL, PROTO_DIS_N1);
	L3AddTimer(&pc->timer, T308, CC_T308_1);
}