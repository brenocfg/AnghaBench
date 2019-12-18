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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  bchannel; } ;
struct l3_process {int debug; int /*<<< orphan*/  timer; int /*<<< orphan*/  st; TYPE_1__ para; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_T313 ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int L3_DEB_WARN ; 
 int /*<<< orphan*/  MT_CONNECT ; 
 int /*<<< orphan*/  T313 ; 
 int /*<<< orphan*/  l3_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  l3dss1_disconnect_req (struct l3_process*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  l3dss1_message (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 

__attribute__((used)) static void
l3dss1_setup_rsp(struct l3_process *pc, u_char pr,
		 void *arg)
{
        if (!pc->para.bchannel) 
	 { if (pc->debug & L3_DEB_WARN)
	       l3_debug(pc->st, "D-chan connect for waiting call");
           l3dss1_disconnect_req(pc, pr, arg);
           return;
         }
	newl3state(pc, 8);
	l3dss1_message(pc, MT_CONNECT);
	L3DelTimer(&pc->timer);
	L3AddTimer(&pc->timer, T313, CC_T313);
}