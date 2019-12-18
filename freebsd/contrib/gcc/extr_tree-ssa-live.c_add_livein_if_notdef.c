#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tree_live_info_p ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  TYPE_2__* basic_block ;
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {int /*<<< orphan*/  global; int /*<<< orphan*/ * livein; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 TYPE_2__* ENTRY_BLOCK_PTR ; 
 int NO_PARTITION ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 
 int var_to_partition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
add_livein_if_notdef (tree_live_info_p live, bitmap def_vec,
		      tree var, basic_block bb)
{
  int p = var_to_partition (live->map, var);
  if (p == NO_PARTITION || bb == ENTRY_BLOCK_PTR)
    return;
  if (!bitmap_bit_p (def_vec, p))
    {
      bitmap_set_bit (live->livein[p], bb->index);
      bitmap_set_bit (live->global, p);
    }
}