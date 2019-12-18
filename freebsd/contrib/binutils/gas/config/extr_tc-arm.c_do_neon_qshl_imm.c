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
struct TYPE_4__ {int /*<<< orphan*/  instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {unsigned int reg; int /*<<< orphan*/  imm; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEON_ENC_IMMED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEON_ENC_INTEGER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_DDD ; 
 int /*<<< orphan*/  NS_DDI ; 
 int /*<<< orphan*/  NS_NULL ; 
 int /*<<< orphan*/  NS_QQI ; 
 int /*<<< orphan*/  NS_QQQ ; 
 scalar_t__ NT_unsigned ; 
 int N_EQK ; 
 int N_KEY ; 
 int N_SGN ; 
 int N_SU_ALL ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int,int,int,...) ; 
 int /*<<< orphan*/  neon_imm_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct neon_type_el,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_quad (int) ; 
 int neon_select_shape (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neon_three_same (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_qshl_imm (void)
{
  if (!inst.operands[2].isreg)
    {
      enum neon_shape rs = neon_select_shape (NS_DDI, NS_QQI, NS_NULL);
      struct neon_type_el et = neon_check_type (2, rs, N_EQK, N_SU_ALL | N_KEY);

      inst.instruction = NEON_ENC_IMMED (inst.instruction);
      neon_imm_shift (TRUE, et.type == NT_unsigned, neon_quad (rs), et,
                      inst.operands[2].imm);
    }
  else
    {
      enum neon_shape rs = neon_select_shape (NS_DDD, NS_QQQ, NS_NULL);
      struct neon_type_el et = neon_check_type (3, rs,
        N_EQK, N_SU_ALL | N_KEY, N_EQK | N_SGN);
      unsigned int tmp;

      /* See note in do_neon_shl_imm.  */
      tmp = inst.operands[2].reg;
      inst.operands[2].reg = inst.operands[1].reg;
      inst.operands[1].reg = tmp;
      inst.instruction = NEON_ENC_INTEGER (inst.instruction);
      neon_three_same (neon_quad (rs), et.type == NT_unsigned, et.size);
    }
}