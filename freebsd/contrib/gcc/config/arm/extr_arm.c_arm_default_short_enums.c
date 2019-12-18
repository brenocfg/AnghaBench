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
 scalar_t__ ARM_ABI_AAPCS_LINUX ; 
 scalar_t__ TARGET_AAPCS_BASED ; 
 scalar_t__ arm_abi ; 

__attribute__((used)) static bool
arm_default_short_enums (void)
{
  return TARGET_AAPCS_BASED && arm_abi != ARM_ABI_AAPCS_LINUX;
}