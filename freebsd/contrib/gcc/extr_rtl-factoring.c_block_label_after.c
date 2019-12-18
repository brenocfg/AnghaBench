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
typedef  scalar_t__ rtx ;
typedef  TYPE_1__* basic_block ;
struct TYPE_7__ {scalar_t__ dest; } ;
struct TYPE_6__ {scalar_t__ next_bb; } ;

/* Variables and functions */
 scalar_t__ BB_END (TYPE_1__*) ; 
 TYPE_1__* BLOCK_FOR_INSN (scalar_t__) ; 
 scalar_t__ EXIT_BLOCK_PTR ; 
 scalar_t__ block_label (scalar_t__) ; 
 TYPE_2__* split_block (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static rtx
block_label_after (rtx insn)
{
  basic_block bb = BLOCK_FOR_INSN (insn);
  if ((insn == BB_END (bb)) && (bb->next_bb != EXIT_BLOCK_PTR))
    return block_label (bb->next_bb);
  else
    return block_label (split_block (bb, insn)->dest);
}