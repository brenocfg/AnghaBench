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
struct neon_type_el {int size; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int HI1 (int /*<<< orphan*/ ) ; 
 int LOW4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_DDDI ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQQI ; 
 int N_16 ; 
 int N_32 ; 
 int N_64 ; 
 int N_8 ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_KEY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int neon_dp_fixup (unsigned int) ; 
 int neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_ext (void)
{
  enum neon_shape rs = neon_select_shape (NS_DDDI, NS_QQQI, NS_NULL);
  struct neon_type_el et = neon_check_type (3, rs,
    N_EQK, N_EQK, N_8 | N_16 | N_32 | N_64 | N_KEY);
  unsigned imm = (inst.operands[3].imm * et.size) / 8;
  constraint (imm >= (neon_quad (rs) ? 16 : 8), _("shift out of range"));
  inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
  inst.instruction |= HI1 (inst.operands[0].reg) << 22;
  inst.instruction |= LOW4 (inst.operands[1].reg) << 16;
  inst.instruction |= HI1 (inst.operands[1].reg) << 7;
  inst.instruction |= LOW4 (inst.operands[2].reg);
  inst.instruction |= HI1 (inst.operands[2].reg) << 5;
  inst.instruction |= neon_quad (rs) << 6;
  inst.instruction |= imm << 8;
  
  inst.instruction = neon_dp_fixup (inst.instruction);
}