#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bc_state {TYPE_2__* cs; int /*<<< orphan*/  channel; } ;
struct TYPE_7__ {int command; int /*<<< orphan*/  arg; int /*<<< orphan*/  driver; } ;
typedef  TYPE_3__ isdn_ctrl ;
struct TYPE_5__ {int /*<<< orphan*/  (* statcallb ) (TYPE_3__*) ;} ;
struct TYPE_6__ {TYPE_1__ iif; int /*<<< orphan*/  myid; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void gigaset_i4l_channel_cmd(struct bc_state *bcs, int cmd)
{
	isdn_ctrl command;

	command.driver = bcs->cs->myid;
	command.command = cmd;
	command.arg = bcs->channel;
	bcs->cs->iif.statcallb(&command);
}