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
typedef  int ia64_insn ;
typedef  enum ia64_insn_type { ____Placeholder_ia64_insn_type } ia64_insn_type ;
struct TYPE_2__ {int insn_index; short priority; scalar_t__ next_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int extract_op (int,int*,unsigned int*) ; 
 TYPE_1__* ia64_dis_names ; 
 scalar_t__ opcode_verify (int,int,int) ; 

__attribute__((used)) static int
locate_opcode_ent (ia64_insn opcode, enum ia64_insn_type type)
{
  int currtest[41];
  int bitpos[41];
  int op_ptr[41];
  int currstatenum = 0;
  short found_disent = -1;
  short found_priority = -1;

  currtest[currstatenum] = 0;
  op_ptr[currstatenum] = 0;
  bitpos[currstatenum] = 40;

  while (1)
    {
      int op_pointer = op_ptr[currstatenum];
      unsigned int op;
      int currbitnum = bitpos[currstatenum];
      int oplen;
      int opval[3] = {0};
      int next_op;
      int currbit;

      oplen = extract_op (op_pointer, opval, &op);

      bitpos[currstatenum] = currbitnum;

      /* Skip opval[0] bits in the instruction. */
      if (op & 0x40)
	{
	  currbitnum -= opval[0];
	}

      /* The value of the current bit being tested. */
      currbit = opcode & (((ia64_insn) 1) << currbitnum) ? 1 : 0;
      next_op = -1;

      /* We always perform the tests specified in the current state in
	 a particular order, falling through to the next test if the
	 previous one failed. */
      switch (currtest[currstatenum])
	{
	case 0:
	  currtest[currstatenum]++;
	  if (currbit == 0 && (op & 0x80))
	    {
	      /* Check for a zero bit.  If this test solely checks for
		 a zero bit, we can check for up to 8 consecutive zero
		 bits (the number to check is specified by the lower 3
		 bits in the state code.)

		 If the state instruction matches, we go to the very
		 next state instruction; otherwise, try the next test. */

	      if ((op & 0xf8) == 0x80)
		{
		  int count = op & 0x7;
		  int x;

		  for (x = 0; x <= count; x++)
		    {
		      int i =
			opcode & (((ia64_insn) 1) << (currbitnum - x)) ? 1 : 0;
		      if (i)
			{
			  break;
			}
		    }
		  if (x > count)
		    {
		      next_op = op_pointer + ((oplen + 7) / 8);
		      currbitnum -= count;
		      break;
		    }
		}
	      else if (! currbit)
		{
		  next_op = op_pointer + ((oplen + 7) / 8);
		  break;
		}
	    }
	  /* FALLTHROUGH */
	case 1:
	  /* If the bit in the instruction is one, go to the state
	     instruction specified by opval[1]. */
	  currtest[currstatenum]++;
	  if (currbit && (op & 0x30) != 0 && ((op & 0x30) != 0x30))
	    {
	      next_op = opval[1];
	      break;
	    }
	  /* FALLTHROUGH */
	case 2:
	  /* Don't care.  Skip the current bit and go to the state
	     instruction specified by opval[2].

	     An encoding of 0x30 is special; this means that a 12-bit
	     offset into the ia64_dis_names[] array is specified.  */
	  currtest[currstatenum]++;
	  if ((op & 0x08) || ((op & 0x30) == 0x30))
	    {
	      next_op = opval[2];
	      break;
	    }
	}

      /* If bit 15 is set in the address of the next state, an offset
	 in the ia64_dis_names array was specified instead.  We then
	 check to see if an entry in the list of opcodes matches the
	 opcode we were given; if so, we have succeeded.  */

      if ((next_op >= 0) && (next_op & 32768))
	{
	  short disent = next_op & 32767;
          short priority = -1;

	  if (next_op > 65535)
	    {
	      abort ();
	    }

	  /* Run through the list of opcodes to check, trying to find
	     one that matches.  */
	  while (disent >= 0)
	    {
	      int place = ia64_dis_names[disent].insn_index;

              priority = ia64_dis_names[disent].priority;

	      if (opcode_verify (opcode, place, type)
                  && priority > found_priority)
		{
		  break;
		}
	      if (ia64_dis_names[disent].next_flag)
		{
		  disent++;
		}
	      else
		{
		  disent = -1;
		}
	    }

	  if (disent >= 0)
	    {
              found_disent = disent;
              found_priority = priority;
	    }
          /* Try the next test in this state, regardless of whether a match
             was found. */
          next_op = -2;
	}

      /* next_op == -1 is "back up to the previous state".
	 next_op == -2 is "stay in this state and try the next test".
	 Otherwise, transition to the state indicated by next_op. */

      if (next_op == -1)
	{
	  currstatenum--;
	  if (currstatenum < 0)
	    {
              return found_disent;
	    }
	}
      else if (next_op >= 0)
	{
	  currstatenum++;
	  bitpos[currstatenum] = currbitnum - 1;
	  op_ptr[currstatenum] = next_op;
	  currtest[currstatenum] = 0;
	}
    }
}