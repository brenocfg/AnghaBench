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
struct sys_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIPER_ICR_R_DIS ; 
 int /*<<< orphan*/  viper_icr_clear_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int viper_cpu_resume(struct sys_device *sysdev)
{
	viper_icr_clear_bit(VIPER_ICR_R_DIS);
	return 0;
}