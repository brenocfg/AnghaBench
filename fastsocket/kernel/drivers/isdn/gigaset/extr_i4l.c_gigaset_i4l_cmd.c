#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;
struct cardstate {TYPE_1__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_5__ {int command; scalar_t__ arg; int /*<<< orphan*/  driver; } ;
typedef  TYPE_2__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void gigaset_i4l_cmd(struct cardstate *cs, int cmd)
{
	isdn_ctrl command;

	command.driver = cs->myid;
	command.command = cmd;
	command.arg = 0;
	cs->iif.statcallb(&command);
}