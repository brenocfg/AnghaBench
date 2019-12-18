#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int X_add_number; scalar_t__ X_op; } ;
struct TYPE_6__ {TYPE_1__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_2__ reloc; TYPE_3__* operands; } ;
struct TYPE_7__ {int reg; scalar_t__ present; } ;

/* Variables and functions */
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ inst ; 

__attribute__((used)) static void
do_t_pkhbt (void)
{
  inst.instruction |= inst.operands[0].reg << 8;
  inst.instruction |= inst.operands[1].reg << 16;
  inst.instruction |= inst.operands[2].reg;
  if (inst.operands[3].present)
    {
      unsigned int val = inst.reloc.exp.X_add_number;
      constraint (inst.reloc.exp.X_op != O_constant,
		  _("expression too complex"));
      inst.instruction |= (val & 0x1c) << 10;
      inst.instruction |= (val & 0x03) << 6;
    }
}