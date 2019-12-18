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
 scalar_t__ flag_tree_copy_prop ; 
 scalar_t__ flag_tree_store_copy_prop ; 

__attribute__((used)) static bool
gate_store_copy_prop (void)
{
  /* STORE-COPY-PROP is enabled only with -ftree-store-copy-prop, but
     when -fno-tree-store-copy-prop is specified, we should run
     regular COPY-PROP. That's why the pass is enabled with either
     flag.  */
  return flag_tree_store_copy_prop != 0 || flag_tree_copy_prop != 0;
}