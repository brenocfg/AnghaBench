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
struct drv_cmd {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_drv_write (struct drv_cmd*) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  smp_call_function_many (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct drv_cmd*),struct drv_cmd*,int) ; 

__attribute__((used)) static void drv_write(struct drv_cmd *cmd)
{
	int this_cpu;

	this_cpu = get_cpu();
	if (cpumask_test_cpu(this_cpu, cmd->mask))
		do_drv_write(cmd);
	smp_call_function_many(cmd->mask, do_drv_write, cmd, 1);
	put_cpu();
}