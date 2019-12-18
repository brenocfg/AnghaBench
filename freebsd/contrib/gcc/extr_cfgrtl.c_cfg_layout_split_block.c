#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* rtx ;
typedef  TYPE_3__* basic_block ;
struct TYPE_9__ {TYPE_1__* rtl; } ;
struct TYPE_10__ {TYPE_2__ il; } ;
struct TYPE_8__ {int /*<<< orphan*/ * footer; } ;

/* Variables and functions */
 TYPE_3__* rtl_split_block (TYPE_3__*,void*) ; 

__attribute__((used)) static basic_block
cfg_layout_split_block (basic_block bb, void *insnp)
{
  rtx insn = insnp;
  basic_block new_bb = rtl_split_block (bb, insn);

  new_bb->il.rtl->footer = bb->il.rtl->footer;
  bb->il.rtl->footer = NULL;

  return new_bb;
}