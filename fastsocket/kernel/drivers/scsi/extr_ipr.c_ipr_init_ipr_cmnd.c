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
struct TYPE_2__ {scalar_t__ scratch; } ;
struct ipr_cmnd {void (* fast_done ) (struct ipr_cmnd*) ;int /*<<< orphan*/  timer; int /*<<< orphan*/ * sibling; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipr_reinit_ipr_cmnd (struct ipr_cmnd*) ; 

__attribute__((used)) static void ipr_init_ipr_cmnd(struct ipr_cmnd *ipr_cmd,
			      void (*fast_done) (struct ipr_cmnd *))
{
	ipr_reinit_ipr_cmnd(ipr_cmd);
	ipr_cmd->u.scratch = 0;
	ipr_cmd->sibling = NULL;
	ipr_cmd->fast_done = fast_done;
	init_timer(&ipr_cmd->timer);
}