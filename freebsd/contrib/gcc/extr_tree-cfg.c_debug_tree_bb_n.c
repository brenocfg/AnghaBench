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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BASIC_BLOCK (int) ; 
 int /*<<< orphan*/  debug_tree_bb (int /*<<< orphan*/ ) ; 

basic_block
debug_tree_bb_n (int n)
{
  debug_tree_bb (BASIC_BLOCK (n));
  return BASIC_BLOCK (n);
}