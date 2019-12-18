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
struct occurrence {int bb_has_division; int /*<<< orphan*/  num_divisions; } ;
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {scalar_t__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_BLOCK_PTR ; 
 int /*<<< orphan*/  insert_bb (struct occurrence*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  occ_head ; 
 struct occurrence* occ_new (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
register_division_in (basic_block bb)
{
  struct occurrence *occ;

  occ = (struct occurrence *) bb->aux;
  if (!occ)
    {
      occ = occ_new (bb, NULL);
      insert_bb (occ, ENTRY_BLOCK_PTR, &occ_head);
    }

  occ->bb_has_division = true;
  occ->num_divisions++;
}