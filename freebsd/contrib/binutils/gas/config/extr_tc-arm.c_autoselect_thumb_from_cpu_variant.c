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
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_ext_v1 ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  opcode_select (int) ; 

__attribute__((used)) static void
autoselect_thumb_from_cpu_variant (void)
{
  if (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v1))
    opcode_select (16);
}