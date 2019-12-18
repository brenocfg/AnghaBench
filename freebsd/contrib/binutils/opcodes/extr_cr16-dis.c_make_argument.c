#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int val; } ;
typedef  TYPE_1__ parameter ;
struct TYPE_7__ {int size; int type; int r; int rp; int pr; int prp; int constant; int cc; int i_r; } ;
typedef  TYPE_2__ argument ;
struct TYPE_8__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRANCH_INS ; 
 int /*<<< orphan*/  CSTBIT_INS ; 
 int /*<<< orphan*/  IS_INSN_MNEMONIC (char*) ; 
 int /*<<< orphan*/  IS_INSN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_STOR_INS ; 
 int /*<<< orphan*/  allWords ; 
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
 TYPE_5__* instruction ; 
 TYPE_1__ makelongparameter (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
make_argument (argument * a, int start_bits)
{
  int inst_bit_size;
  parameter p;

  if ((instruction->size == 3) && a->size >= 16)
    inst_bit_size = 48;
  else
    inst_bit_size = 32;

  switch (a->type)
    {
    case arg_r:
      p = makelongparameter (allWords, inst_bit_size - (start_bits + a->size),
                             inst_bit_size - start_bits);
      a->r = p.val;
      break;

    case arg_rp:
      p = makelongparameter (allWords, inst_bit_size - (start_bits + a->size),
                             inst_bit_size - start_bits);
      a->rp = p.val;
      break;

    case arg_pr:
      p = makelongparameter (allWords, inst_bit_size - (start_bits + a->size),
                             inst_bit_size - start_bits);
      a->pr = p.val;
      break;

    case arg_prp:
      p = makelongparameter (allWords, inst_bit_size - (start_bits + a->size),
                             inst_bit_size - start_bits);
      a->prp = p.val;
      break;

    case arg_ic:
      p = makelongparameter (allWords, inst_bit_size - (start_bits + a->size),
                             inst_bit_size - start_bits);
      a->constant = p.val;
      break;

    case arg_cc:
      p = makelongparameter (allWords, inst_bit_size - (start_bits + a->size),
                             inst_bit_size - start_bits);

      a->cc = p.val;
      break;

    case arg_idxr:
      if ((IS_INSN_MNEMONIC ("cbitb"))
	  || (IS_INSN_MNEMONIC ("sbitb"))
	  || (IS_INSN_MNEMONIC ("tbitb")))
	p = makelongparameter (allWords, 8, 9);
      else
	p = makelongparameter (allWords, 9, 10);
      a->i_r = p.val;
      p = makelongparameter (allWords, inst_bit_size - a->size, inst_bit_size);
      a->constant = p.val;
      break;

    case arg_idxrp:
      p = makelongparameter (allWords, start_bits + 12, start_bits + 13);
      a->i_r = p.val;
      p = makelongparameter (allWords, start_bits + 13, start_bits + 16);
      a->rp = p.val;
      if (inst_bit_size > 32)
	{
	  p = makelongparameter (allWords, inst_bit_size - start_bits - 12,
				 inst_bit_size);
	  a->constant = ((p.val & 0xffff) | (p.val >> 8 & 0xf0000));
	}
      else if (instruction->size == 2)
	{
	  p = makelongparameter (allWords, inst_bit_size - 22, inst_bit_size);
	  a->constant = (p.val & 0xf) | (((p.val >>20) & 0x3) << 4)
	    | ((p.val >>14 & 0x3) << 6) | (((p.val >>7) & 0x1f) <<7);
	}
      else if (instruction->size == 1 && a->size == 0)
	a->constant = 0;

      break;

    case arg_rbase:
      p = makelongparameter (allWords, inst_bit_size, inst_bit_size);
      a->constant = p.val;
      p = makelongparameter (allWords, inst_bit_size - (start_bits + 4),
                             inst_bit_size - start_bits);
      a->r = p.val;
      break;

    case arg_cr:
      p = makelongparameter (allWords, start_bits + 12, start_bits + 16);
      a->r = p.val;
      p = makelongparameter (allWords, inst_bit_size - 16, inst_bit_size);
      a->constant = p.val;
      break;

    case arg_crp:
      if (instruction->size == 1)
	p = makelongparameter (allWords, 12, 16);
      else
	p = makelongparameter (allWords, start_bits + 12, start_bits + 16);
      a->rp = p.val;

      if (inst_bit_size > 32)
	{
	  p = makelongparameter (allWords, inst_bit_size - start_bits - 12,
				 inst_bit_size);
	  a->constant = ((p.val & 0xffff) | (p.val >> 8 & 0xf0000));
	}
      else if (instruction->size == 2)
	{
	  p = makelongparameter (allWords, inst_bit_size - 16, inst_bit_size);
	  a->constant = p.val;
	}
      else if (instruction->size == 1 && a->size != 0)
	{
	  p = makelongparameter (allWords, 4, 8);
	  if (IS_INSN_MNEMONIC ("loadw")
	      || IS_INSN_MNEMONIC ("loadd")
	      || IS_INSN_MNEMONIC ("storw")
	      || IS_INSN_MNEMONIC ("stord"))
	    a->constant = (p.val * 2);
	  else
	    a->constant = p.val;
	}
      else /* below case for 0x0(reg pair) */
	a->constant = 0;

      break;

    case arg_c:

      if ((IS_INSN_TYPE (BRANCH_INS))
	  || (IS_INSN_MNEMONIC ("bal"))
	  || (IS_INSN_TYPE (CSTBIT_INS))
	  || (IS_INSN_TYPE (LD_STOR_INS)))
	{
	  switch (a->size)
	    {
	    case 8 :
	      p = makelongparameter (allWords, 0, start_bits);
	      a->constant = ((((p.val&0xf00)>>4)) | (p.val&0xf));
	      break;

	    case 24:
	      if (instruction->size == 3)
		{
		  p = makelongparameter (allWords, 16, inst_bit_size);
		  a->constant = ((((p.val>>16)&0xf) << 20)
				 | (((p.val>>24)&0xf) << 16)
				 | (p.val & 0xffff));
		}
	      else if (instruction->size == 2)
		{
		  p = makelongparameter (allWords, 8, inst_bit_size);
		  a->constant = p.val;
		}
	      break;

	    default:
	      p = makelongparameter (allWords, inst_bit_size - (start_bits +
								a->size), inst_bit_size - start_bits);
	      a->constant = p.val;
	      break;
	    }
	}
      else
	{
	  p = makelongparameter (allWords, inst_bit_size -
				 (start_bits + a->size),
				 inst_bit_size - start_bits);
	  a->constant = p.val;
	}
      break;

    default:
      break;
    }
}