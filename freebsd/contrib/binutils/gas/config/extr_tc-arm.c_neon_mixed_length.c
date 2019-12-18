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
struct neon_type_el {scalar_t__ type; } ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int HI1 (int /*<<< orphan*/ ) ; 
 int LOW4 (int /*<<< orphan*/ ) ; 
 scalar_t__ NT_unsigned ; 
 TYPE_2__ inst ; 
 int neon_dp_fixup (int) ; 
 int neon_logbits (unsigned int) ; 

__attribute__((used)) static void
neon_mixed_length (struct neon_type_el et, unsigned size)
{
  inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
  inst.instruction |= HI1 (inst.operands[0].reg) << 22;
  inst.instruction |= LOW4 (inst.operands[1].reg) << 16;
  inst.instruction |= HI1 (inst.operands[1].reg) << 7;
  inst.instruction |= LOW4 (inst.operands[2].reg);
  inst.instruction |= HI1 (inst.operands[2].reg) << 5;
  inst.instruction |= (et.type == NT_unsigned) << 24;
  inst.instruction |= neon_logbits (size) << 20;
  
  inst.instruction = neon_dp_fixup (inst.instruction);
}