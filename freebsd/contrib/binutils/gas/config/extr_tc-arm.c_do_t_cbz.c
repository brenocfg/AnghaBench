#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int pc_rel; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int instruction; TYPE_2__ reloc; TYPE_1__* operands; } ;
struct TYPE_4__ {int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_HIREG ; 
 int /*<<< orphan*/  BAD_NOT_IT ; 
 int /*<<< orphan*/  BFD_RELOC_THUMB_PCREL_BRANCH7 ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int current_it_mask ; 
 TYPE_3__ inst ; 

__attribute__((used)) static void
do_t_cbz (void)
{
  constraint (current_it_mask, BAD_NOT_IT);
  constraint (inst.operands[0].reg > 7, BAD_HIREG);
  inst.instruction |= inst.operands[0].reg;
  inst.reloc.pc_rel = 1;
  inst.reloc.type = BFD_RELOC_THUMB_PCREL_BRANCH7;
}