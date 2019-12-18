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

/* Variables and functions */
 int /*<<< orphan*/  arm_machine_restart (char,char const*) ; 
 int /*<<< orphan*/  mioa701_machine_exit () ; 

__attribute__((used)) static void mioa701_restart(char c, const char *cmd)
{
	mioa701_machine_exit();
	arm_machine_restart('s', cmd);
}