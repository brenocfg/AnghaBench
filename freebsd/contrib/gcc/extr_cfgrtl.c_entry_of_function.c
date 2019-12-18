#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  next_bb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* ENTRY_BLOCK_PTR ; 
 scalar_t__ NUM_FIXED_BLOCKS ; 
 int /*<<< orphan*/  get_insns () ; 
 scalar_t__ n_basic_blocks ; 

rtx
entry_of_function (void)
{
  return (n_basic_blocks > NUM_FIXED_BLOCKS ?
	  BB_HEAD (ENTRY_BLOCK_PTR->next_bb) : get_insns ());
}