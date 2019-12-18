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
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int instruction; TYPE_2__ reloc; TYPE_1__* operands; } ;
struct TYPE_4__ {int reg; scalar_t__ negative; scalar_t__ shifted; scalar_t__ immisreg; scalar_t__ writeback; scalar_t__ postind; int /*<<< orphan*/  preind; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ADDR_MODE ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_T32_OFFSET_U8 ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ inst ; 

__attribute__((used)) static void
do_t_strex (void)
{
  constraint (!inst.operands[2].isreg || !inst.operands[2].preind
	      || inst.operands[2].postind || inst.operands[2].writeback
	      || inst.operands[2].immisreg || inst.operands[2].shifted
	      || inst.operands[2].negative,
	      BAD_ADDR_MODE);

  inst.instruction |= inst.operands[0].reg << 8;
  inst.instruction |= inst.operands[1].reg << 12;
  inst.instruction |= inst.operands[2].reg << 16;
  inst.reloc.type = BFD_RELOC_ARM_T32_OFFSET_U8;
}