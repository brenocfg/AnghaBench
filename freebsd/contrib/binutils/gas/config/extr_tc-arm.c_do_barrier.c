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
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  constraint (int,char*) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_barrier (void)
{
  if (inst.operands[0].present)
    {
      constraint ((inst.instruction & 0xf0) != 0x40
		  && (inst.instruction & 0xf0) != 0x50
		  && inst.operands[0].imm != 0xf,
		  "bad barrier type");
      inst.instruction |= inst.operands[0].imm;
    }
  else
    inst.instruction |= 0xf;
}