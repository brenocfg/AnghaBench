#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* basic_block ;
struct TYPE_5__ {scalar_t__ object; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_DIRTY ; 
 TYPE_1__* BLOCK_FOR_INSN (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 TYPE_2__* changes ; 
 int num_changes ; 

void
confirm_change_group (void)
{
  int i;
  basic_block bb;

  for (i = 0; i < num_changes; i++)
    if (changes[i].object
	&& INSN_P (changes[i].object)
	&& (bb = BLOCK_FOR_INSN (changes[i].object)))
      bb->flags |= BB_DIRTY;

  num_changes = 0;
}