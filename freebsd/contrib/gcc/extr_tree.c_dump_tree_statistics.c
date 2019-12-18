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
struct TYPE_2__ {int /*<<< orphan*/  (* print_statistics ) () ;} ;

/* Variables and functions */
 scalar_t__ all_kinds ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  phinodes_print_statistics () ; 
 int /*<<< orphan*/  print_debug_expr_statistics () ; 
 int /*<<< orphan*/  print_restrict_base_statistics () ; 
 int /*<<< orphan*/  print_type_hash_statistics () ; 
 int /*<<< orphan*/  print_value_expr_statistics () ; 
 int /*<<< orphan*/  ssanames_print_statistics () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stub1 () ; 
 int* tree_node_counts ; 
 char** tree_node_kind_names ; 
 int* tree_node_sizes ; 

void
dump_tree_statistics (void)
{
#ifdef GATHER_STATISTICS
  int i;
  int total_nodes, total_bytes;
#endif

  fprintf (stderr, "\n??? tree nodes created\n\n");
#ifdef GATHER_STATISTICS
  fprintf (stderr, "Kind                   Nodes      Bytes\n");
  fprintf (stderr, "---------------------------------------\n");
  total_nodes = total_bytes = 0;
  for (i = 0; i < (int) all_kinds; i++)
    {
      fprintf (stderr, "%-20s %7d %10d\n", tree_node_kind_names[i],
	       tree_node_counts[i], tree_node_sizes[i]);
      total_nodes += tree_node_counts[i];
      total_bytes += tree_node_sizes[i];
    }
  fprintf (stderr, "---------------------------------------\n");
  fprintf (stderr, "%-20s %7d %10d\n", "Total", total_nodes, total_bytes);
  fprintf (stderr, "---------------------------------------\n");
  ssanames_print_statistics ();
  phinodes_print_statistics ();
#else
  fprintf (stderr, "(No per-node statistics)\n");
#endif
  print_type_hash_statistics ();
  print_debug_expr_statistics ();
  print_value_expr_statistics ();
  print_restrict_base_statistics ();
  lang_hooks.print_statistics ();
}