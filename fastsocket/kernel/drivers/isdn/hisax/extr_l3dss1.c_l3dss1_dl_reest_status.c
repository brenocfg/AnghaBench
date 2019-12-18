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
struct TYPE_2__ {int cause; } ;
struct l3_process {TYPE_1__ para; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3dss1_status_send (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l3dss1_dl_reest_status(struct l3_process *pc, u_char pr, void *arg)
{
	L3DelTimer(&pc->timer);
 
 	pc->para.cause = 0x1F; /* normal, unspecified */
	l3dss1_status_send(pc, 0, NULL);
}