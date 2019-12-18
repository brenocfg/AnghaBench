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
struct TYPE_4__ {int size_req; int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; } ;

/* Variables and functions */
 int THUMB_OP32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_MNEM_mov ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_cpy (void)
{
  if (inst.size_req == 4)
    {
      inst.instruction = THUMB_OP32 (T_MNEM_mov);
      inst.instruction |= inst.operands[0].reg << 8;
      inst.instruction |= inst.operands[1].reg;
    }
  else
    {
      inst.instruction |= (inst.operands[0].reg & 0x8) << 4;
      inst.instruction |= (inst.operands[0].reg & 0x7);
      inst.instruction |= inst.operands[1].reg << 3;
    }
}