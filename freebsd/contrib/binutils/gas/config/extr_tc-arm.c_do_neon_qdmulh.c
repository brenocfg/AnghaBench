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
struct neon_type_el {int /*<<< orphan*/  size; } ;
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_4__ {int /*<<< orphan*/  instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {scalar_t__ isscalar; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEON_ENC_INTEGER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEON_ENC_SCALAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_DDD ; 
 int /*<<< orphan*/  NS_DDS ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQQ ; 
 int /*<<< orphan*/  NS_QQS ; 
 int /*<<< orphan*/  N_EQK ; 
 int N_KEY ; 
 int N_S16 ; 
 int N_S32 ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  neon_mul_mac (struct neon_type_el,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_three_same (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_qdmulh (void)
{
  if (inst.operands[2].isscalar)
    {
      enum neon_shape rs = neon_select_shape (NS_DDS, NS_QQS, NS_NULL);
      struct neon_type_el et = neon_check_type (3, rs,
        N_EQK, N_EQK, N_S16 | N_S32 | N_KEY);
      inst.instruction = NEON_ENC_SCALAR (inst.instruction);
      neon_mul_mac (et, neon_quad (rs));
    }
  else
    {
      enum neon_shape rs = neon_select_shape (NS_DDD, NS_QQQ, NS_NULL);
      struct neon_type_el et = neon_check_type (3, rs,
        N_EQK, N_EQK, N_S16 | N_S32 | N_KEY);
      inst.instruction = NEON_ENC_INTEGER (inst.instruction);
      /* The U bit (rounding) comes from bit mask.  */
      neon_three_same (neon_quad (rs), 0, et.size);
    }
}