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
typedef  scalar_t__ tree ;
typedef  TYPE_1__* basic_block ;
struct TYPE_3__ {size_t index; } ;

/* Variables and functions */
 scalar_t__* label_for_bb ; 
 TYPE_1__* label_to_block (scalar_t__) ; 

__attribute__((used)) static tree
main_block_label (tree label)
{
  basic_block bb = label_to_block (label);

  /* label_to_block possibly inserted undefined label into the chain.  */
  if (!label_for_bb[bb->index])
    label_for_bb[bb->index] = label;
  return label_for_bb[bb->index];
}