#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; scalar_t__ isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  INST_IMMEDIATE ; 
 int /*<<< orphan*/  encode_arm_shift (int) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
encode_arm_shifter_operand (int i)
{
  if (inst.operands[i].isreg)
    {
      inst.instruction |= inst.operands[i].reg;
      encode_arm_shift (i);
    }
  else
    inst.instruction |= INST_IMMEDIATE;
}