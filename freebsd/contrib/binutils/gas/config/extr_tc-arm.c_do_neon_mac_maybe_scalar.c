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
struct neon_type_el {int dummy; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int /*<<< orphan*/  instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {scalar_t__ isscalar; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int NEON_CHECK_ARCH ; 
 int NEON_CHECK_CC ; 
 int /*<<< orphan*/  NEON_ENC_SCALAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_DDS ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQS ; 
 int /*<<< orphan*/  NT_untyped ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_F32 ; 
 int N_I16 ; 
 int N_I32 ; 
 int /*<<< orphan*/  N_IF_32 ; 
 int N_KEY ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  do_vfp_nsyn_mla_mls ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neon_dyadic_misc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_mul_mac (struct neon_type_el,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ try_vfp_nsyn (int,int /*<<< orphan*/ ) ; 
 scalar_t__ vfp_or_neon_is_neon (int) ; 

__attribute__((used)) static void
do_neon_mac_maybe_scalar (void)
{
  if (try_vfp_nsyn (3, do_vfp_nsyn_mla_mls) == SUCCESS)
    return;

  if (vfp_or_neon_is_neon (NEON_CHECK_CC | NEON_CHECK_ARCH) == FAIL)
    return;

  if (inst.operands[2].isscalar)
    {
      enum neon_shape rs = neon_select_shape (NS_DDS, NS_QQS, NS_NULL);
      struct neon_type_el et = neon_check_type (3, rs,
        N_EQK, N_EQK, N_I16 | N_I32 | N_F32 | N_KEY);
      inst.instruction = NEON_ENC_SCALAR (inst.instruction);
      neon_mul_mac (et, neon_quad (rs));
    }
  else
    {
      /* The "untyped" case can't happen.  Do this to stop the "U" bit being
	 affected if we specify unsigned args.  */
      neon_dyadic_misc (NT_untyped, N_IF_32, 0);
    }
}