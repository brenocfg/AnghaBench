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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int TDF_UID ; 
 int TDF_VOPS ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stderr ; 

void
debug_tree_chain (tree t)
{
  while (t)
  {
    print_generic_expr (stderr, t, TDF_VOPS|TDF_UID);
    fprintf(stderr, " ");
    t = TREE_CHAIN (t);
  }
  fprintf (stderr, "\n");
}