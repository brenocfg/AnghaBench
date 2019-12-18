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
struct neon_type_el {int size; scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DQI ; 
 scalar_t__ NT_unsigned ; 
 int N_EQK ; 
 int N_HLF ; 
 int N_KEY ; 
 int /*<<< orphan*/  N_MNEM_vqmovn ; 
 int N_SU_16_64 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_neon_qmovn () ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  neon_imm_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct neon_type_el,int) ; 

__attribute__((used)) static void
do_neon_rshift_sat_narrow (void)
{
  /* FIXME: Types for narrowing. If operands are signed, results can be signed
     or unsigned. If operands are unsigned, results must also be unsigned.  */
  struct neon_type_el et = neon_check_type (2, NS_DQI,
    N_EQK | N_HLF, N_SU_16_64 | N_KEY);
  int imm = inst.operands[2].imm;
  /* This gets the bounds check, size encoding and immediate bits calculation
     right.  */
  et.size /= 2;
  
  /* VQ{R}SHRN.I<size> <Dd>, <Qm>, #0 is a synonym for
     VQMOVN.I<size> <Dd>, <Qm>.  */
  if (imm == 0)
    {
      inst.operands[2].present = 0;
      inst.instruction = N_MNEM_vqmovn;
      do_neon_qmovn ();
      return;
    }
  
  constraint (imm < 1 || (unsigned)imm > et.size,
              _("immediate out of range"));
  neon_imm_shift (TRUE, et.type == NT_unsigned, 0, et, et.size - imm);
}