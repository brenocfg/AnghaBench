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
struct TYPE_3__ {unsigned int reg; scalar_t__ isscalar; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int HI1 (unsigned int) ; 
 int LOW4 (unsigned int) ; 
 int /*<<< orphan*/  NEON_CHECK_CC ; 
 unsigned int NEON_ENC_ARMREG (unsigned int) ; 
 int NEON_ENC_SCALAR (int) ; 
 int NEON_SCALAR_INDEX (unsigned int) ; 
 unsigned int NEON_SCALAR_REG (unsigned int) ; 
 int /*<<< orphan*/  NS_DR ; 
 int /*<<< orphan*/  NS_DS ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QR ; 
 int /*<<< orphan*/  NS_QS ; 
 int N_16 ; 
 int N_32 ; 
 int N_8 ; 
 int N_EQK ; 
 int N_KEY ; 
 int /*<<< orphan*/  do_vfp_cond_or_thumb () ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int,int,int) ; 
 unsigned int neon_dp_fixup (unsigned int) ; 
 int neon_logbits (int) ; 
 int neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vfp_or_neon_is_neon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_dup (void)
{
  if (inst.operands[1].isscalar)
    {
      enum neon_shape rs = neon_select_shape (NS_DS, NS_QS, NS_NULL);
      struct neon_type_el et = neon_check_type (2, rs,
        N_EQK, N_8 | N_16 | N_32 | N_KEY);
      unsigned sizebits = et.size >> 3;
      unsigned dm = NEON_SCALAR_REG (inst.operands[1].reg);
      int logsize = neon_logbits (et.size);
      unsigned x = NEON_SCALAR_INDEX (inst.operands[1].reg) << logsize;

      if (vfp_or_neon_is_neon (NEON_CHECK_CC) == FAIL)
        return;

      inst.instruction = NEON_ENC_SCALAR (inst.instruction);
      inst.instruction |= LOW4 (inst.operands[0].reg) << 12;
      inst.instruction |= HI1 (inst.operands[0].reg) << 22;
      inst.instruction |= LOW4 (dm);
      inst.instruction |= HI1 (dm) << 5;
      inst.instruction |= neon_quad (rs) << 6;
      inst.instruction |= x << 17;
      inst.instruction |= sizebits << 16;
      
      inst.instruction = neon_dp_fixup (inst.instruction);
    }
  else
    {
      enum neon_shape rs = neon_select_shape (NS_DR, NS_QR, NS_NULL);
      struct neon_type_el et = neon_check_type (2, rs,
        N_8 | N_16 | N_32 | N_KEY, N_EQK);
      /* Duplicate ARM register to lanes of vector.  */
      inst.instruction = NEON_ENC_ARMREG (inst.instruction);
      switch (et.size)
        {
        case 8:  inst.instruction |= 0x400000; break;
        case 16: inst.instruction |= 0x000020; break;
        case 32: inst.instruction |= 0x000000; break;
        default: break;
        }
      inst.instruction |= LOW4 (inst.operands[1].reg) << 12;
      inst.instruction |= LOW4 (inst.operands[0].reg) << 16;
      inst.instruction |= HI1 (inst.operands[0].reg) << 7;
      inst.instruction |= neon_quad (rs) << 21;
      /* The encoding for this instruction is identical for the ARM and Thumb
         variants, except for the condition field.  */
      do_vfp_cond_or_thumb ();
    }
}