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
typedef  int /*<<< orphan*/  arm_mvfp_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpuid_mvfp_info ; 

arm_mvfp_info_t *
machine_arm_mvfp_info(void)
{
	return &cpuid_mvfp_info;
}