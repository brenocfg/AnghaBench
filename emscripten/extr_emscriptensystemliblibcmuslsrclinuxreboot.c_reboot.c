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
 int /*<<< orphan*/  SYS_reboot ; 
 int syscall (int /*<<< orphan*/ ,int,int,int) ; 

int reboot(int type)
{
	return syscall(SYS_reboot, 0xfee1dead, 672274793, type);
}