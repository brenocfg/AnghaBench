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
struct megasas_instance {int /*<<< orphan*/  reg_set; TYPE_1__* instancet; } ;
struct megasas_cmd {int /*<<< orphan*/  frame_phys_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fire_cmd ) (struct megasas_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct megasas_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
megasas_issue_dcmd(struct megasas_instance *instance, struct megasas_cmd *cmd)
{
	instance->instancet->fire_cmd(instance,
		cmd->frame_phys_addr, 0, instance->reg_set);
}