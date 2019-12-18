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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/ * edge ;
typedef  scalar_t__ basic_block ;

/* Variables and functions */
 int /*<<< orphan*/ * find_edge (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ label_to_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static edge
find_taken_edge_computed_goto (basic_block bb, tree val)
{
  basic_block dest;
  edge e = NULL;

  dest = label_to_block (val);
  if (dest)
    {
      e = find_edge (bb, dest);
      gcc_assert (e != NULL);
    }

  return e;
}