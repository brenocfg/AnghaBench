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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; scalar_t__ isreg; } ;

/* Variables and functions */
 int HI1 (int /*<<< orphan*/ ) ; 
 int LOW4 (int /*<<< orphan*/ ) ; 
 int NEON_ENC_IMMED (int) ; 
 int /*<<< orphan*/  NS_DDI ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQI ; 
 scalar_t__ NT_float ; 
 int /*<<< orphan*/  NT_unsigned ; 
 int N_EQK ; 
 unsigned int N_KEY ; 
 int N_SIZ ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int,int,unsigned int) ; 
 int neon_dp_fixup (int) ; 
 int /*<<< orphan*/  neon_dyadic_misc (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  neon_exchange_operands () ; 
 int neon_logbits (int /*<<< orphan*/ ) ; 
 int neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
neon_compare (unsigned regtypes, unsigned immtypes, int invert)
{
  if (inst.operands[2].isreg)
    {
      if (invert)
        neon_exchange_operands ();
      neon_dyadic_misc (NT_unsigned, regtypes, N_SIZ);
    }
  else
    {
      enum neon_shape rs = neon_select_shape (NS_DDI, NS_QQI, NS_NULL);
      struct neon_type_el et = neon_check_type (2, rs,
        N_EQK | N_SIZ, immtypes | N_KEY);

      inst.instruction = NEON_ENC_IMMED (inst.instruction);
      inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
      inst.instruction |= HI1 (inst.operands[0].reg) << 22;
      inst.instruction |= LOW4 (inst.operands[1].reg);
      inst.instruction |= HI1 (inst.operands[1].reg) << 5;
      inst.instruction |= neon_quad (rs) << 6;
      inst.instruction |= (et.type == NT_float) << 10;
      inst.instruction |= neon_logbits (et.size) << 18;
      
      inst.instruction = neon_dp_fixup (inst.instruction);
    }
}