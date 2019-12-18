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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* BASIC_BLOCK (unsigned int) ; 
 int /*<<< orphan*/  BB_DUPLICATED ; 
 int /*<<< orphan*/  add_phi_args_after_copy_bb (TYPE_1__*) ; 
 scalar_t__ last_basic_block ; 

__attribute__((used)) static void
copy_phi_node_args (unsigned first_new_block)
{
  unsigned i;

  for (i = first_new_block; i < (unsigned) last_basic_block; i++)
    BASIC_BLOCK (i)->flags |= BB_DUPLICATED;

  for (i = first_new_block; i < (unsigned) last_basic_block; i++)
    add_phi_args_after_copy_bb (BASIC_BLOCK (i));

  for (i = first_new_block; i < (unsigned) last_basic_block; i++)
    BASIC_BLOCK (i)->flags &= ~BB_DUPLICATED;
}