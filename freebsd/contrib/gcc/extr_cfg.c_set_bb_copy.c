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
struct htab_bb_copy_original_entry {int /*<<< orphan*/  index2; int /*<<< orphan*/  index1; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  bb_copy ; 
 scalar_t__ htab_find_slot (int /*<<< orphan*/ ,struct htab_bb_copy_original_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ original_copy_bb_pool ; 
 struct htab_bb_copy_original_entry* pool_alloc (scalar_t__) ; 

void
set_bb_copy (basic_block bb, basic_block copy)
{
  if (original_copy_bb_pool)
    {
      struct htab_bb_copy_original_entry **slot;
      struct htab_bb_copy_original_entry key;

      key.index1 = bb->index;
      slot =
	(struct htab_bb_copy_original_entry **) htab_find_slot (bb_copy,
							       &key, INSERT);
      if (*slot)
	(*slot)->index2 = copy->index;
      else
	{
	  *slot = pool_alloc (original_copy_bb_pool);
	  (*slot)->index1 = bb->index;
	  (*slot)->index2 = copy->index;
	}
    }
}