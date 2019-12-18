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
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 void* VEC_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edge ; 
 void* edge_leader ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  leader_has_match ; 
 void* stmt_list ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void
init_analyze_edges_for_bb (void)
{
  edge_leader = VEC_alloc (edge, heap, 25);
  stmt_list = VEC_alloc (tree, heap, 25);
  leader_has_match = BITMAP_ALLOC (NULL);
}