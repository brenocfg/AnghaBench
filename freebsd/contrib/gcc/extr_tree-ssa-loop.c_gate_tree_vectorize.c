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
 scalar_t__ current_loops ; 
 scalar_t__ flag_tree_vectorize ; 

__attribute__((used)) static bool
gate_tree_vectorize (void)
{
  return flag_tree_vectorize && current_loops;
}