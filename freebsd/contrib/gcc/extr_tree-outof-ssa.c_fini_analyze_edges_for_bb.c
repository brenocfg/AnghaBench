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
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edge ; 
 int /*<<< orphan*/  edge_leader ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  leader_has_match ; 
 int /*<<< orphan*/  stmt_list ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void
fini_analyze_edges_for_bb (void)
{
  VEC_free (edge, heap, edge_leader);
  VEC_free (tree, heap, stmt_list);
  BITMAP_FREE (leader_has_match);
}