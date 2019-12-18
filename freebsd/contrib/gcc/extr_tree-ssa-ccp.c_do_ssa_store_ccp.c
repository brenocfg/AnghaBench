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
 int /*<<< orphan*/  execute_ssa_ccp (int) ; 
 scalar_t__ flag_tree_store_ccp ; 

__attribute__((used)) static unsigned int
do_ssa_store_ccp (void)
{
  /* If STORE-CCP is not enabled, we just run regular CCP.  */
  execute_ssa_ccp (flag_tree_store_ccp != 0);
  return 0;
}