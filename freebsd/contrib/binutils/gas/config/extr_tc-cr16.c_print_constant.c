#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  long constant ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  constant; } ;
typedef  TYPE_1__ argument ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR16_PRINT (int,long,int) ; 
 int /*<<< orphan*/  IS_INSN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_STOR_INS ; 
 long WORD_SHIFT ; 
 int /*<<< orphan*/  arg_idxrp ; 
 long getconstant (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* instruction ; 

__attribute__((used)) static void
print_constant (int nbits, int shift, argument *arg)
{
  unsigned long mask = 0;

  long constant = getconstant (arg->constant, nbits);

  switch (nbits)
    {
    case 32:
    case 28:
      /* mask the upper part of the constant, that is, the bits
	 going to the lowest byte of output_opcode[0].
	 The upper part of output_opcode[1] is always filled,
	 therefore it is always masked with 0xFFFF.  */
      mask = (1 << (nbits - 16)) - 1;
      /* Divide the constant between two consecutive words :
	 0        1         2         3
	 +---------+---------+---------+---------+
	 |         | X X X X | x X x X |         |
	 +---------+---------+---------+---------+
	 output_opcode[0]    output_opcode[1]     */

      CR16_PRINT (0, (constant >> WORD_SHIFT) & mask, 0);
      CR16_PRINT (1, (constant & 0xFFFF), WORD_SHIFT);
      break;

    case 21:
      if ((nbits == 21) && (IS_INSN_TYPE (LD_STOR_INS))) nbits = 20;
    case 24:
    case 22:
    case 20:
      /* mask the upper part of the constant, that is, the bits
	 going to the lowest byte of output_opcode[0].
	 The upper part of output_opcode[1] is always filled,
	 therefore it is always masked with 0xFFFF.  */
      mask = (1 << (nbits - 16)) - 1;
      /* Divide the constant between two consecutive words :
	 0        1         2          3
	 +---------+---------+---------+---------+
	 |         | X X X X | - X - X |         |
	 +---------+---------+---------+---------+
	 output_opcode[0]    output_opcode[1]     */

      if ((instruction->size > 2) && (shift == WORD_SHIFT))
	{
	  if (arg->type == arg_idxrp)
	    {
	      CR16_PRINT (0, ((constant >> WORD_SHIFT) & mask) << 8, 0);
	      CR16_PRINT (1, (constant & 0xFFFF), WORD_SHIFT);
	    }
	  else
	    {
	      CR16_PRINT (0, (((((constant >> WORD_SHIFT) & mask) << 8) & 0x0f00) | ((((constant >> WORD_SHIFT) & mask) >> 4) & 0xf)),0);
	      CR16_PRINT (1, (constant & 0xFFFF), WORD_SHIFT);
	    }
	}
      else
	CR16_PRINT (0, constant, shift);
      break;

    case 14:
      if (arg->type == arg_idxrp)
	{
	  if (instruction->size == 2)
	    {
	      CR16_PRINT (0, ((constant)&0xf), shift);         // 0-3 bits
	      CR16_PRINT (0, ((constant>>4)&0x3), (shift+20)); // 4-5 bits
	      CR16_PRINT (0, ((constant>>6)&0x3), (shift+14)); // 6-7 bits
	      CR16_PRINT (0, ((constant>>8)&0x3f), (shift+8)); // 8-13 bits
	    }
	  else
	    CR16_PRINT (0, constant, shift);
	}
      break;

    case 16:
    case 12:
      /* When instruction size is 3 and 'shift' is 16, a 16-bit constant is
	 always filling the upper part of output_opcode[1]. If we mistakenly
	 write it to output_opcode[0], the constant prefix (that is, 'match')
	 will be overriden.
	 0        1         2         3
	 +---------+---------+---------+---------+
	 | 'match' |         | X X X X |         |
	 +---------+---------+---------+---------+
	 output_opcode[0]    output_opcode[1]     */

      if ((instruction->size > 2) && (shift == WORD_SHIFT))
	CR16_PRINT (1, constant, WORD_SHIFT);
      else
	CR16_PRINT (0, constant, shift);
      break;

    case 8:
      CR16_PRINT (0, ((constant/2)&0xf), shift);
      CR16_PRINT (0, ((constant/2)>>4),  (shift+8));
      break;

    default:
      CR16_PRINT (0, constant,  shift);
      break;
    }
}