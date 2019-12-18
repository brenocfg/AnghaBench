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
struct eh_region {int dummy; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int EDGE_ABNORMAL ; 
 int EDGE_EH ; 
 int /*<<< orphan*/  bb_for_stmt (scalar_t__) ; 
 scalar_t__ get_eh_region_tree_label (struct eh_region*) ; 
 int /*<<< orphan*/  label_to_block (scalar_t__) ; 
 int /*<<< orphan*/  make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
make_eh_edge (struct eh_region *region, void *data)
{
  tree stmt, lab;
  basic_block src, dst;

  stmt = (tree) data;
  lab = get_eh_region_tree_label (region);

  src = bb_for_stmt (stmt);
  dst = label_to_block (lab);

  make_edge (src, dst, EDGE_ABNORMAL | EDGE_EH);
}