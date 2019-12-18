#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; int cc; int /*<<< orphan*/  rp; int /*<<< orphan*/  r; int /*<<< orphan*/  i_r; int /*<<< orphan*/  prp; int /*<<< orphan*/  pr; } ;
typedef  TYPE_1__ argument ;
struct TYPE_6__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR16_PRINT (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CSTBIT_INS ; 
 int /*<<< orphan*/  IS_INSN_MNEMONIC (char*) ; 
 int /*<<< orphan*/  IS_INSN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_STOR_INS ; 
#define  arg_c 139 
#define  arg_cc 138 
#define  arg_cr 137 
#define  arg_crp 136 
#define  arg_ic 135 
#define  arg_idxr 134 
#define  arg_idxrp 133 
#define  arg_pr 132 
#define  arg_prp 131 
#define  arg_r 130 
#define  arg_rbase 129 
#define  arg_rp 128 
 int getidxregp_image (int /*<<< orphan*/ ) ; 
 int getprocreg_image (int /*<<< orphan*/ ) ; 
 int getprocregp_image (int /*<<< orphan*/ ) ; 
 int getreg_image (int /*<<< orphan*/ ) ; 
 int getregp_image (int /*<<< orphan*/ ) ; 
 TYPE_4__* instruction ; 
 int /*<<< orphan*/  print_constant (int,int,TYPE_1__*) ; 

__attribute__((used)) static void
print_operand (int nbits, int shift, argument *arg)
{
  switch (arg->type)
    {
    case arg_cc:
      CR16_PRINT (0, arg->cc, shift);
      break;

    case arg_r:
      CR16_PRINT (0, getreg_image (arg->r), shift);
      break;

    case arg_rp:
      CR16_PRINT (0, getregp_image (arg->rp), shift);
      break;

    case arg_pr:
      CR16_PRINT (0, getprocreg_image (arg->pr), shift);
      break;

    case arg_prp:
      CR16_PRINT (0, getprocregp_image (arg->prp), shift);
      break;

    case arg_idxrp:
      /*    16      12      8    6      0
            +-----------------------------+
            | r_index | disp  | rp_base   |
            +-----------------------------+          */

      if (instruction->size == 3)
	{
	  CR16_PRINT (0, getidxregp_image (arg->rp), 0);
	  if (getreg_image (arg->i_r) == 12)
	    CR16_PRINT (0, 0, 3);
	  else
	    CR16_PRINT (0, 1, 3);
	}
      else
	{
	  CR16_PRINT (0, getidxregp_image (arg->rp), 16);
	  if (getreg_image (arg->i_r) == 12)
	    CR16_PRINT (0, 0, 19);
	  else
	    CR16_PRINT (0, 1, 19);
	}
      print_constant (nbits, shift, arg);
      break;

    case arg_idxr:
      if (getreg_image (arg->i_r) == 12)
	if (IS_INSN_MNEMONIC ("cbitb") || IS_INSN_MNEMONIC ("sbitb")
	    || IS_INSN_MNEMONIC ("tbitb"))
	  CR16_PRINT (0, 0, 23);
	else CR16_PRINT (0, 0, 24);
      else
	if (IS_INSN_MNEMONIC ("cbitb") || IS_INSN_MNEMONIC ("sbitb")
	    || IS_INSN_MNEMONIC ("tbitb"))
	  CR16_PRINT (0, 1, 23);
	else CR16_PRINT (0, 1, 24);

      print_constant (nbits, shift, arg);
      break;

    case arg_ic:
    case arg_c:
      print_constant (nbits, shift, arg);
      break;

    case arg_rbase:
      CR16_PRINT (0, getreg_image (arg->r), shift);
      break;

    case arg_cr:
      print_constant (nbits, shift , arg);
      /* Add the register argument to the output_opcode.  */
      CR16_PRINT (0, getreg_image (arg->r), (shift+16));
      break;

    case arg_crp:
      print_constant (nbits, shift , arg);
      if (instruction->size > 1)
	CR16_PRINT (0, getregp_image (arg->rp), (shift + 16));
      else if (IS_INSN_TYPE (LD_STOR_INS) || (IS_INSN_TYPE (CSTBIT_INS)))
	{
	  if (instruction->size == 2)
	    CR16_PRINT (0, getregp_image (arg->rp), (shift - 8));
	  else if (instruction->size == 1)
	    CR16_PRINT (0, getregp_image (arg->rp), 16);
	}
      else
	CR16_PRINT (0, getregp_image (arg->rp), shift);
      break;

    default:
      break;
    }
}