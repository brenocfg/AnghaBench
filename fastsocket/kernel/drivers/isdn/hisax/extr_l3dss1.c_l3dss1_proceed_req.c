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
struct l3_process {TYPE_2__* st; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_2__*,int,struct l3_process*) ;} ;
struct TYPE_4__ {TYPE_1__ l3; } ;

/* Variables and functions */
 int CC_PROCEED_SEND ; 
 int INDICATION ; 
 int /*<<< orphan*/  MT_CALL_PROCEEDING ; 
 int /*<<< orphan*/  l3dss1_message (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3dss1_proceed_req(struct l3_process *pc, u_char pr,
		   void *arg)
{
	newl3state(pc, 9);
	l3dss1_message(pc, MT_CALL_PROCEEDING);
	pc->st->l3.l3l4(pc->st, CC_PROCEED_SEND | INDICATION, pc); 
}