#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct def_blocks_d {int /*<<< orphan*/  phi_blocks; int /*<<< orphan*/  def_blocks; } ;
typedef  enum need_phi_state { ____Placeholder_need_phi_state } need_phi_state ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEED_PHI_STATE_MAYBE ; 
 int /*<<< orphan*/  NEED_PHI_STATE_NO ; 
 int NEED_PHI_STATE_UNKNOWN ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct def_blocks_d* get_def_blocks_for (int /*<<< orphan*/ ) ; 
 int get_phi_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_phi_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_def_block (tree var, basic_block bb, bool phi_p)
{
  struct def_blocks_d *db_p;
  enum need_phi_state state;

  state = get_phi_state (var);
  db_p = get_def_blocks_for (var);

  /* Set the bit corresponding to the block where VAR is defined.  */
  bitmap_set_bit (db_p->def_blocks, bb->index);
  if (phi_p)
    bitmap_set_bit (db_p->phi_blocks, bb->index);

  /* Keep track of whether or not we may need to insert PHI nodes.

     If we are in the UNKNOWN state, then this is the first definition
     of VAR.  Additionally, we have not seen any uses of VAR yet, so
     we do not need a PHI node for this variable at this time (i.e.,
     transition to NEED_PHI_STATE_NO).

     If we are in any other state, then we either have multiple definitions
     of this variable occurring in different blocks or we saw a use of the
     variable which was not dominated by the block containing the
     definition(s).  In this case we may need a PHI node, so enter
     state NEED_PHI_STATE_MAYBE.  */
  if (state == NEED_PHI_STATE_UNKNOWN)
    set_phi_state (var, NEED_PHI_STATE_NO);
  else
    set_phi_state (var, NEED_PHI_STATE_MAYBE);
}