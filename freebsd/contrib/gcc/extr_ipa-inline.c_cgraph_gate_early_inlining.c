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
 scalar_t__ flag_early_inlining ; 
 scalar_t__ flag_inline_trees ; 

__attribute__((used)) static bool
cgraph_gate_early_inlining (void)
{
  return flag_inline_trees && flag_early_inlining;
}