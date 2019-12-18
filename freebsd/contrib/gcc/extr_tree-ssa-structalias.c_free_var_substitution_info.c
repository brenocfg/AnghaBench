#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scc_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  direct_nodes; int /*<<< orphan*/  eq_rep; int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_obstack_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_scc_info (struct scc_info*) ; 
 TYPE_1__* graph ; 
 int /*<<< orphan*/  iteration_obstack ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_var_substitution_info (struct scc_info *si)
{
  free_scc_info (si);
  free (graph->label);
  free (graph->eq_rep);
  sbitmap_free (graph->direct_nodes);
  bitmap_obstack_release (&iteration_obstack);
}