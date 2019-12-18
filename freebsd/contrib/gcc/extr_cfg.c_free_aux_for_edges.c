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
 int /*<<< orphan*/  clear_aux_for_edges () ; 
 int /*<<< orphan*/  edge_aux_obstack ; 
 int /*<<< orphan*/ * first_edge_aux_obj ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
free_aux_for_edges (void)
{
  gcc_assert (first_edge_aux_obj);
  obstack_free (&edge_aux_obstack, first_edge_aux_obj);
  first_edge_aux_obj = NULL;

  clear_aux_for_edges ();
}