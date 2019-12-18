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
 int /*<<< orphan*/  init_tree_ssa () ; 

__attribute__((used)) static unsigned int
execute_init_datastructures (void)
{
  /* Allocate hash tables, arrays and other structures.  */
  init_tree_ssa ();
  return 0;
}