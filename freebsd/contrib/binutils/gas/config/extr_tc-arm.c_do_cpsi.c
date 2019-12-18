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
 int CPSI_MMOD ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_cpsi (void)
{
  inst.instruction |= inst.operands[0].imm << 6;
  if (inst.operands[1].present)
    {
      inst.instruction |= CPSI_MMOD;
      inst.instruction |= inst.operands[1].imm;
    }
}