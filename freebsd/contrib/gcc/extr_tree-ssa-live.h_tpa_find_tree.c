#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tpa_p ;
struct TYPE_4__ {int* partition_to_tree_map; int uncompressed_num; } ;

/* Variables and functions */
 int TPA_NONE ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int tpa_num_trees (TYPE_1__*) ; 

__attribute__((used)) static inline int 
tpa_find_tree (tpa_p tpa, int i)
{
  int index;

  index = tpa->partition_to_tree_map[i];
  /* When compressed, any index higher than the number of tree elements is 
     a compressed element, so return TPA_NONE.  */
  if (index != TPA_NONE && index >= tpa_num_trees (tpa))
    {
      gcc_assert (tpa->uncompressed_num != -1);
      index = TPA_NONE;
    }

  return index;
}