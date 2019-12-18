#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ADDR_BITS_REMOVE (scalar_t__) ; 
 unsigned long ARM_PS_REGNUM ; 
 scalar_t__ BranchDest (scalar_t__,unsigned long) ; 
 unsigned long FLAG_C ; 
 unsigned long INST_NV ; 
 scalar_t__ arm_pc_is_thumb (scalar_t__) ; 
 int bit (unsigned long,int) ; 
 int bitcount (unsigned long) ; 
 unsigned long bits (unsigned long,int,int) ; 
 scalar_t__ condition_true (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 unsigned long read_memory_integer (scalar_t__,int) ; 
 unsigned long read_register (unsigned long) ; 
 unsigned long shifted_reg_val (unsigned long,int,unsigned long,unsigned long) ; 
 scalar_t__ thumb_get_next_pc (scalar_t__) ; 

CORE_ADDR
arm_get_next_pc (CORE_ADDR pc)
{
  unsigned long pc_val;
  unsigned long this_instr;
  unsigned long status;
  CORE_ADDR nextpc;

  if (arm_pc_is_thumb (pc))
    return thumb_get_next_pc (pc);

  pc_val = (unsigned long) pc;
  this_instr = read_memory_integer (pc, 4);
  status = read_register (ARM_PS_REGNUM);
  nextpc = (CORE_ADDR) (pc_val + 4);	/* Default case */

  if (condition_true (bits (this_instr, 28, 31), status))
    {
      switch (bits (this_instr, 24, 27))
	{
	case 0x0:
	case 0x1:			/* data processing */
	case 0x2:
	case 0x3:
	  {
	    unsigned long operand1, operand2, result = 0;
	    unsigned long rn;
	    int c;

	    if (bits (this_instr, 12, 15) != 15)
	      break;

	    if (bits (this_instr, 22, 25) == 0
		&& bits (this_instr, 4, 7) == 9)	/* multiply */
	      error ("Illegal update to pc in instruction");

	    /* BX <reg>, BLX <reg> */
	    if (bits (this_instr, 4, 28) == 0x12fff1
		|| bits (this_instr, 4, 28) == 0x12fff3)
	      {
		rn = bits (this_instr, 0, 3);
		result = (rn == 15) ? pc_val + 8 : read_register (rn);
		nextpc = (CORE_ADDR) ADDR_BITS_REMOVE (result);

		if (nextpc == pc)
		  error ("Infinite loop detected");

		return nextpc;
	      }

	    /* Multiply into PC */
	    c = (status & FLAG_C) ? 1 : 0;
	    rn = bits (this_instr, 16, 19);
	    operand1 = (rn == 15) ? pc_val + 8 : read_register (rn);

	    if (bit (this_instr, 25))
	      {
		unsigned long immval = bits (this_instr, 0, 7);
		unsigned long rotate = 2 * bits (this_instr, 8, 11);
		operand2 = ((immval >> rotate) | (immval << (32 - rotate)))
		  & 0xffffffff;
	      }
	    else		/* operand 2 is a shifted register */
	      operand2 = shifted_reg_val (this_instr, c, pc_val, status);

	    switch (bits (this_instr, 21, 24))
	      {
	      case 0x0:	/*and */
		result = operand1 & operand2;
		break;

	      case 0x1:	/*eor */
		result = operand1 ^ operand2;
		break;

	      case 0x2:	/*sub */
		result = operand1 - operand2;
		break;

	      case 0x3:	/*rsb */
		result = operand2 - operand1;
		break;

	      case 0x4:	/*add */
		result = operand1 + operand2;
		break;

	      case 0x5:	/*adc */
		result = operand1 + operand2 + c;
		break;

	      case 0x6:	/*sbc */
		result = operand1 - operand2 + c;
		break;

	      case 0x7:	/*rsc */
		result = operand2 - operand1 + c;
		break;

	      case 0x8:
	      case 0x9:
	      case 0xa:
	      case 0xb:	/* tst, teq, cmp, cmn */
		result = (unsigned long) nextpc;
		break;

	      case 0xc:	/*orr */
		result = operand1 | operand2;
		break;

	      case 0xd:	/*mov */
		/* Always step into a function.  */
		result = operand2;
		break;

	      case 0xe:	/*bic */
		result = operand1 & ~operand2;
		break;

	      case 0xf:	/*mvn */
		result = ~operand2;
		break;
	      }
	    nextpc = (CORE_ADDR) ADDR_BITS_REMOVE (result);

	    if (nextpc == pc)
	      error ("Infinite loop detected");
	    break;
	  }

	case 0x4:
	case 0x5:		/* data transfer */
	case 0x6:
	case 0x7:
	  if (bit (this_instr, 20))
	    {
	      /* load */
	      if (bits (this_instr, 12, 15) == 15)
		{
		  /* rd == pc */
		  unsigned long rn;
		  unsigned long base;

		  if (bit (this_instr, 22))
		    error ("Illegal update to pc in instruction");

		  /* byte write to PC */
		  rn = bits (this_instr, 16, 19);
		  base = (rn == 15) ? pc_val + 8 : read_register (rn);
		  if (bit (this_instr, 24))
		    {
		      /* pre-indexed */
		      int c = (status & FLAG_C) ? 1 : 0;
		      unsigned long offset =
		      (bit (this_instr, 25)
		       ? shifted_reg_val (this_instr, c, pc_val, status)
		       : bits (this_instr, 0, 11));

		      if (bit (this_instr, 23))
			base += offset;
		      else
			base -= offset;
		    }
		  nextpc = (CORE_ADDR) read_memory_integer ((CORE_ADDR) base,
							    4);

		  nextpc = ADDR_BITS_REMOVE (nextpc);

		  if (nextpc == pc)
		    error ("Infinite loop detected");
		}
	    }
	  break;

	case 0x8:
	case 0x9:		/* block transfer */
	  if (bit (this_instr, 20))
	    {
	      /* LDM */
	      if (bit (this_instr, 15))
		{
		  /* loading pc */
		  int offset = 0;

		  if (bit (this_instr, 23))
		    {
		      /* up */
		      unsigned long reglist = bits (this_instr, 0, 14);
		      offset = bitcount (reglist) * 4;
		      if (bit (this_instr, 24))		/* pre */
			offset += 4;
		    }
		  else if (bit (this_instr, 24))
		    offset = -4;

		  {
		    unsigned long rn_val =
		    read_register (bits (this_instr, 16, 19));
		    nextpc =
		      (CORE_ADDR) read_memory_integer ((CORE_ADDR) (rn_val
								  + offset),
						       4);
		  }
		  nextpc = ADDR_BITS_REMOVE (nextpc);
		  if (nextpc == pc)
		    error ("Infinite loop detected");
		}
	    }
	  break;

	case 0xb:		/* branch & link */
	case 0xa:		/* branch */
	  {
	    nextpc = BranchDest (pc, this_instr);

	    /* BLX */
	    if (bits (this_instr, 28, 31) == INST_NV)
	      nextpc |= bit (this_instr, 24) << 1;

	    nextpc = ADDR_BITS_REMOVE (nextpc);
	    if (nextpc == pc)
	      error ("Infinite loop detected");
	    break;
	  }

	case 0xc:
	case 0xd:
	case 0xe:		/* coproc ops */
	case 0xf:		/* SWI */
	  break;

	default:
	  fprintf_filtered (gdb_stderr, "Bad bit-field extraction\n");
	  return (pc);
	}
    }

  return nextpc;
}