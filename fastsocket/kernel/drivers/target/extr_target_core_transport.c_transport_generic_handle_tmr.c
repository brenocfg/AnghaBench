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
struct se_cmd {int /*<<< orphan*/  work; TYPE_1__* se_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_tmr_work ; 

int transport_generic_handle_tmr(
	struct se_cmd *cmd)
{
	INIT_WORK(&cmd->work, target_tmr_work);
	queue_work(cmd->se_dev->tmr_wq, &cmd->work);
	return 0;
}