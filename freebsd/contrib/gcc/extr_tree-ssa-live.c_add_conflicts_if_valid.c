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
typedef  int /*<<< orphan*/  var_map ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  tpa_p ;
typedef  int /*<<< orphan*/  conflict_graph ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 int NO_PARTITION ; 
 int TPA_NONE ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  conflict_graph_add (int /*<<< orphan*/ ,int,int) ; 
 int tpa_find_tree (int /*<<< orphan*/ ,int) ; 
 int tpa_first_partition (int /*<<< orphan*/ ,int) ; 
 int tpa_next_partition (int /*<<< orphan*/ ,int) ; 
 int var_to_partition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void 
add_conflicts_if_valid (tpa_p tpa, conflict_graph graph,
			var_map map, bitmap vec, tree var)
{ 
  int p, y, first;
  p = var_to_partition (map, var);
  if (p != NO_PARTITION)
    { 
      bitmap_clear_bit (vec, p);
      first = tpa_find_tree (tpa, p);
      /* If find returns nothing, this object isn't interesting.  */
      if (first == TPA_NONE)
        return;
      /* Only add interferences between objects in the same list.  */
      for (y = tpa_first_partition (tpa, first);
	   y != TPA_NONE;
	   y = tpa_next_partition (tpa, y))
	{
	  if (bitmap_bit_p (vec, y))
	    conflict_graph_add (graph, p, y);
	}
    }
}