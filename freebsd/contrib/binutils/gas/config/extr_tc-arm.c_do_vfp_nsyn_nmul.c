#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_2__ {int /*<<< orphan*/  instruction; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEON_ENC_DOUBLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEON_ENC_SINGLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_DDD ; 
 int NS_FFF ; 
 int /*<<< orphan*/  NS_NULL ; 
 int N_EQK ; 
 int N_F32 ; 
 int N_F64 ; 
 int N_KEY ; 
 int N_VFP ; 
 int /*<<< orphan*/  do_vfp_cond_or_thumb () ; 
 int /*<<< orphan*/  do_vfp_dp_rd_rn_rm () ; 
 int /*<<< orphan*/  do_vfp_sp_dyadic () ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  neon_check_type (int,int,int,int,int) ; 
 int neon_select_shape (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_vfp_nsyn_nmul (void)
{
  enum neon_shape rs = neon_select_shape (NS_FFF, NS_DDD, NS_NULL);
  neon_check_type (3, rs, N_EQK | N_VFP, N_EQK | N_VFP,
    N_F32 | N_F64 | N_KEY | N_VFP);
  
  if (rs == NS_FFF)
    {
      inst.instruction = NEON_ENC_SINGLE (inst.instruction);
      do_vfp_sp_dyadic ();
    }
  else
    {
      inst.instruction = NEON_ENC_DOUBLE (inst.instruction);
      do_vfp_dp_rd_rn_rm ();
    }
  do_vfp_cond_or_thumb ();
}