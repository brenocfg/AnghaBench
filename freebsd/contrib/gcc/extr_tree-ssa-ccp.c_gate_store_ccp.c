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
 scalar_t__ flag_tree_ccp ; 
 scalar_t__ flag_tree_store_ccp ; 

__attribute__((used)) static bool
gate_store_ccp (void)
{
  /* STORE-CCP is enabled only with -ftree-store-ccp, but when
     -fno-tree-store-ccp is specified, we should run regular CCP.
     That's why the pass is enabled with either flag.  */
  return flag_tree_store_ccp != 0 || flag_tree_ccp != 0;
}