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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NS_DQI ; 
 int N_EQK ; 
 int N_HLF ; 
 int N_I16 ; 
 int N_I32 ; 
 int N_I64 ; 
 int N_KEY ; 
 int /*<<< orphan*/  N_MNEM_vmovn ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_neon_movn () ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  neon_imm_shift (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct neon_type_el,int) ; 

__attribute__((used)) static void
do_neon_rshift_narrow (void)
{
  struct neon_type_el et = neon_check_type (2, NS_DQI,
    N_EQK | N_HLF, N_I16 | N_I32 | N_I64 | N_KEY);
  int imm = inst.operands[2].imm;
  /* This gets the bounds check, size encoding and immediate bits calculation
     right.  */
  et.size /= 2;
  
  /* If immediate is zero then we are a pseudo-instruction for
     VMOVN.I<size> <Dd>, <Qm>  */
  if (imm == 0)
    {
      inst.operands[2].present = 0;
      inst.instruction = N_MNEM_vmovn;
      do_neon_movn ();
      return;
    }
  
  constraint (imm < 1 || (unsigned)imm > et.size,
              _("immediate out of range for narrowing operation"));
  neon_imm_shift (FALSE, 0, 0, et, et.size - imm);
}