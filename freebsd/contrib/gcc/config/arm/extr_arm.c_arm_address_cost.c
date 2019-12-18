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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ TARGET_ARM ; 
 int arm_arm_address_cost (int /*<<< orphan*/ ) ; 
 int arm_thumb_address_cost (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_address_cost (rtx x)
{
  return TARGET_ARM ? arm_arm_address_cost (x) : arm_thumb_address_cost (x);
}