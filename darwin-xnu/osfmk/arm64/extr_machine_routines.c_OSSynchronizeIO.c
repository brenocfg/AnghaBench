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
 int /*<<< orphan*/  DSB_SY ; 
 int /*<<< orphan*/  __builtin_arm_dsb (int /*<<< orphan*/ ) ; 

void OSSynchronizeIO(void)
{
	__builtin_arm_dsb(DSB_SY);
}