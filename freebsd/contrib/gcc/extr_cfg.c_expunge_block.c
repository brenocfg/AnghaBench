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
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BASIC_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_basic_blocks ; 
 int /*<<< orphan*/  unlink_block (TYPE_1__*) ; 

void
expunge_block (basic_block b)
{
  unlink_block (b);
  SET_BASIC_BLOCK (b->index, NULL);
  n_basic_blocks--;
  /* We should be able to ggc_free here, but we are not.
     The dead SSA_NAMES are left pointing to dead statements that are pointing
     to dead basic blocks making garbage collector to die.
     We should be able to release all dead SSA_NAMES and at the same time we should
     clear out BB pointer of dead statements consistently.  */
}