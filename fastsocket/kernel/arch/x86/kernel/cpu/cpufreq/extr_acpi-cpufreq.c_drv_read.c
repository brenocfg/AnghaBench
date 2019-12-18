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
struct drv_cmd {int /*<<< orphan*/  mask; scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_drv_read ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drv_cmd*,int) ; 

__attribute__((used)) static void drv_read(struct drv_cmd *cmd)
{
	cmd->val = 0;

	smp_call_function_single(cpumask_any(cmd->mask), do_drv_read, cmd, 1);
}