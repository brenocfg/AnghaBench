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
struct TYPE_4__ {int /*<<< orphan*/  instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DQI ; 
 int N_EQK ; 
 int N_HLF ; 
 int N_KEY ; 
 int /*<<< orphan*/  N_MNEM_vqmovun ; 
 int N_S16 ; 
 int N_S32 ; 
 int N_S64 ; 
 int N_UNS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_neon_qmovun () ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  neon_imm_shift (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct neon_type_el,int) ; 

__attribute__((used)) static void
do_neon_rshift_sat_narrow_u (void)
{
  /* FIXME: Types for narrowing. If operands are signed, results can be signed
     or unsigned. If operands are unsigned, results must also be unsigned.  */
  struct neon_type_el et = neon_check_type (2, NS_DQI,
    N_EQK | N_HLF | N_UNS, N_S16 | N_S32 | N_S64 | N_KEY);
  int imm = inst.operands[2].imm;
  /* This gets the bounds check, size encoding and immediate bits calculation
     right.  */
  et.size /= 2;

  /* VQSHRUN.I<size> <Dd>, <Qm>, #0 is a synonym for
     VQMOVUN.I<size> <Dd>, <Qm>.  */
  if (imm == 0)
    {
      inst.operands[2].present = 0;
      inst.instruction = N_MNEM_vqmovun;
      do_neon_qmovun ();
      return;
    }

  constraint (imm < 1 || (unsigned)imm > et.size,
              _("immediate out of range"));
  /* FIXME: The manual is kind of unclear about what value U should have in
     VQ{R}SHRUN instructions, but U=0, op=0 definitely encodes VRSHR, so it
     must be 1.  */
  neon_imm_shift (TRUE, 1, 0, et, et.size - imm);
}