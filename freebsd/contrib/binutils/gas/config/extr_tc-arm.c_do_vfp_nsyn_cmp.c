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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {scalar_t__ isreg; } ;

/* Variables and functions */
 void* NEON_ENC_DOUBLE (int) ; 
 void* NEON_ENC_SINGLE (int) ; 
 int /*<<< orphan*/  NS_DD ; 
 int /*<<< orphan*/  NS_DI ; 
 int NS_FF ; 
 int NS_FI ; 
 int /*<<< orphan*/  NS_NULL ; 
 int N_EQK ; 
 int N_F32 ; 
 int N_F64 ; 
 int N_KEY ; 
#define  N_MNEM_vcmp 129 
#define  N_MNEM_vcmpe 128 
 int const N_MNEM_vcmpez ; 
 int const N_MNEM_vcmpz ; 
 int N_VFP ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  do_vfp_cond_or_thumb () ; 
 int /*<<< orphan*/  do_vfp_dp_rd () ; 
 int /*<<< orphan*/  do_vfp_dp_rd_rm () ; 
 int /*<<< orphan*/  do_vfp_sp_compare_z () ; 
 int /*<<< orphan*/  do_vfp_sp_monadic () ; 
 TYPE_2__ inst ; 
 int /*<<< orphan*/  neon_check_type (int,int,int,int) ; 
 int neon_select_shape (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_vfp_nsyn_cmp (void)
{
  if (inst.operands[1].isreg)
    {
      enum neon_shape rs = neon_select_shape (NS_FF, NS_DD, NS_NULL);
      neon_check_type (2, rs, N_EQK | N_VFP, N_F32 | N_F64 | N_KEY | N_VFP);
      
      if (rs == NS_FF)
        {
          inst.instruction = NEON_ENC_SINGLE (inst.instruction);
          do_vfp_sp_monadic ();
        }
      else
        {
          inst.instruction = NEON_ENC_DOUBLE (inst.instruction);
          do_vfp_dp_rd_rm ();
        }
    }
  else
    {
      enum neon_shape rs = neon_select_shape (NS_FI, NS_DI, NS_NULL);
      neon_check_type (2, rs, N_F32 | N_F64 | N_KEY | N_VFP, N_EQK);

      switch (inst.instruction & 0x0fffffff)
        {
        case N_MNEM_vcmp:
          inst.instruction += N_MNEM_vcmpz - N_MNEM_vcmp;
          break;
        case N_MNEM_vcmpe:
          inst.instruction += N_MNEM_vcmpez - N_MNEM_vcmpe;
          break;
        default:
          abort ();
        }
     
      if (rs == NS_FI)
        {
          inst.instruction = NEON_ENC_SINGLE (inst.instruction);
          do_vfp_sp_compare_z ();
        }
      else
        {
          inst.instruction = NEON_ENC_DOUBLE (inst.instruction);
          do_vfp_dp_rd ();
        }
    }
  do_vfp_cond_or_thumb ();
}