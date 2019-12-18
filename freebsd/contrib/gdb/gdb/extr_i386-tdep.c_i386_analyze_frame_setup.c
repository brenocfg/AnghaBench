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
struct i386_frame_cache {int sp_offset; int locals; scalar_t__* saved_regs; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 size_t I386_EBP_REGNUM ; 
 void* read_memory_integer (scalar_t__,int) ; 
 int read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
i386_analyze_frame_setup (CORE_ADDR pc, CORE_ADDR current_pc,
			  struct i386_frame_cache *cache)
{
  unsigned char op;
  int skip = 0;

  if (current_pc <= pc)
    return current_pc;

  op = read_memory_unsigned_integer (pc, 1);

  if (op == 0x55)		/* pushl %ebp */
    {
      /* Take into account that we've executed the `pushl %ebp' that
	 starts this instruction sequence.  */
      cache->saved_regs[I386_EBP_REGNUM] = 0;
      cache->sp_offset += 4;

      /* If that's all, return now.  */
      if (current_pc <= pc + 1)
	return current_pc;

      op = read_memory_unsigned_integer (pc + 1, 1);

      /* Check for some special instructions that might be migrated
	 by GCC into the prologue.  We check for

	    xorl %ebx, %ebx
	    xorl %ecx, %ecx
	    xorl %edx, %edx
	    xorl %eax, %eax

	 and the equivalent

	    subl %ebx, %ebx
	    subl %ecx, %ecx
	    subl %edx, %edx
	    subl %eax, %eax

	 Because of the symmetry, there are actually two ways to
	 encode these instructions; with opcode bytes 0x29 and 0x2b
	 for `subl' and opcode bytes 0x31 and 0x33 for `xorl'.

	 Make sure we only skip these instructions if we later see the
	 `movl %esp, %ebp' that actually sets up the frame.  */
      while (op == 0x29 || op == 0x2b || op == 0x31 || op == 0x33)
	{
	  op = read_memory_unsigned_integer (pc + skip + 2, 1);
	  switch (op)
	    {
	    case 0xdb:	/* %ebx */
	    case 0xc9:	/* %ecx */
	    case 0xd2:	/* %edx */
	    case 0xc0:	/* %eax */
	      skip += 2;
	      break;
	    default:
	      return pc + 1;
	    }

	  op = read_memory_unsigned_integer (pc + skip + 1, 1);
	}

      /* Check for `movl %esp, %ebp' -- can be written in two ways.  */
      switch (op)
	{
	case 0x8b:
	  if (read_memory_unsigned_integer (pc + skip + 2, 1) != 0xec)
	    return pc + 1;
	  break;
	case 0x89:
	  if (read_memory_unsigned_integer (pc + skip + 2, 1) != 0xe5)
	    return pc + 1;
	  break;
	default:
	  return pc + 1;
	}

      /* OK, we actually have a frame.  We just don't know how large
	 it is yet.  Set its size to zero.  We'll adjust it if
	 necessary.  We also now commit to skipping the special
	 instructions mentioned before.  */
      cache->locals = 0;
      pc += skip;

      /* If that's all, return now.  */
      if (current_pc <= pc + 3)
	return current_pc;

      /* Check for stack adjustment 

	    subl $XXX, %esp

	 NOTE: You can't subtract a 16 bit immediate from a 32 bit
	 reg, so we don't have to worry about a data16 prefix.  */
      op = read_memory_unsigned_integer (pc + 3, 1);
      if (op == 0x83)
	{
	  /* `subl' with 8 bit immediate.  */
	  if (read_memory_unsigned_integer (pc + 4, 1) != 0xec)
	    /* Some instruction starting with 0x83 other than `subl'.  */
	    return pc + 3;

	  /* `subl' with signed byte immediate (though it wouldn't make
	     sense to be negative).  */
	  cache->locals = read_memory_integer (pc + 5, 1);
	  return pc + 6;
	}
      else if (op == 0x81)
	{
	  /* Maybe it is `subl' with a 32 bit immedediate.  */
	  if (read_memory_unsigned_integer (pc + 4, 1) != 0xec)
	    /* Some instruction starting with 0x81 other than `subl'.  */
	    return pc + 3;

	  /* It is `subl' with a 32 bit immediate.  */
	  cache->locals = read_memory_integer (pc + 5, 4);
	  return pc + 9;
	}
      else
	{
	  /* Some instruction other than `subl'.  */
	  return pc + 3;
	}
    }
  else if (op == 0xc8)		/* enter $XXX */
    {
      cache->locals = read_memory_unsigned_integer (pc + 1, 2);
      return pc + 4;
    }

  return pc;
}