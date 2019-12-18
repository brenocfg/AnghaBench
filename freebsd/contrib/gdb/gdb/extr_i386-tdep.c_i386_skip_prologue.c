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
struct i386_frame_cache {int locals; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ i386_analyze_prologue (scalar_t__,int,struct i386_frame_cache*) ; 
 scalar_t__ i386_follow_jump (scalar_t__) ; 
 int read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
i386_skip_prologue (CORE_ADDR start_pc)
{
  static unsigned char pic_pat[6] =
  {
    0xe8, 0, 0, 0, 0,		/* call 0x0 */
    0x5b,			/* popl %ebx */
  };
  struct i386_frame_cache cache;
  CORE_ADDR pc;
  unsigned char op;
  int i;

  cache.locals = -1;
  pc = i386_analyze_prologue (start_pc, 0xffffffff, &cache);
  if (cache.locals < 0)
    return start_pc;

  /* Found valid frame setup.  */

  /* The native cc on SVR4 in -K PIC mode inserts the following code
     to get the address of the global offset table (GOT) into register
     %ebx:

        call	0x0
	popl    %ebx
        movl    %ebx,x(%ebp)    (optional)
        addl    y,%ebx

     This code is with the rest of the prologue (at the end of the
     function), so we have to skip it to get to the first real
     instruction at the start of the function.  */

  for (i = 0; i < 6; i++)
    {
      op = read_memory_unsigned_integer (pc + i, 1);
      if (pic_pat[i] != op)
	break;
    }
  if (i == 6)
    {
      int delta = 6;

      op = read_memory_unsigned_integer (pc + delta, 1);

      if (op == 0x89)		/* movl %ebx, x(%ebp) */
	{
	  op = read_memory_unsigned_integer (pc + delta + 1, 1);

	  if (op == 0x5d)	/* One byte offset from %ebp.  */
	    delta += 3;
	  else if (op == 0x9d)	/* Four byte offset from %ebp.  */
	    delta += 6;
	  else			/* Unexpected instruction.  */
	    delta = 0;

	  op = read_memory_unsigned_integer (pc + delta, 1);
	}

      /* addl y,%ebx */
      if (delta > 0 && op == 0x81
	  && read_memory_unsigned_integer (pc + delta + 1, 1) == 0xc3)
	{
	  pc += delta + 6;
	}
    }

  return i386_follow_jump (pc);
}