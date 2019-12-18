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
struct neon_type_el {scalar_t__ type; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {unsigned int reg; } ;

/* Variables and functions */
 int HI1 (unsigned int) ; 
 int LOW4 (unsigned int) ; 
 scalar_t__ NT_float ; 
 scalar_t__ NT_invtype ; 
 TYPE_2__ inst ; 
 int neon_dp_fixup (int) ; 
 int neon_logbits (int /*<<< orphan*/ ) ; 
 unsigned int neon_scalar_for_mul (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
neon_mul_mac (struct neon_type_el et, int ubit)
{
  unsigned scalar;

  /* Give a more helpful error message if we have an invalid type.  */
  if (et.type == NT_invtype)
    return;
  
  scalar = neon_scalar_for_mul (inst.operands[2].reg, et.size);
  inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
  inst.instruction |= HI1 (inst.operands[0].reg) << 22;
  inst.instruction |= LOW4 (inst.operands[1].reg) << 16;
  inst.instruction |= HI1 (inst.operands[1].reg) << 7;
  inst.instruction |= LOW4 (scalar);
  inst.instruction |= HI1 (scalar) << 5;
  inst.instruction |= (et.type == NT_float) << 8;
  inst.instruction |= neon_logbits (et.size) << 20;
  inst.instruction |= (ubit != 0) << 24;

  inst.instruction = neon_dp_fixup (inst.instruction);
}