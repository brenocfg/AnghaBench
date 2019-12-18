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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_SPECIAL_POOL_ENTRY_P (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
rs6000_use_blocks_for_constant_p (enum machine_mode mode, rtx x)
{
  return !ASM_OUTPUT_SPECIAL_POOL_ENTRY_P (x, mode);
}