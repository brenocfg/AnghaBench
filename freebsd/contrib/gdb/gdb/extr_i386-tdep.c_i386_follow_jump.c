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
 long read_memory_integer (scalar_t__,int) ; 
 unsigned char read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
i386_follow_jump (CORE_ADDR pc)
{
  unsigned char op;
  long delta = 0;
  int data16 = 0;

  op = read_memory_unsigned_integer (pc, 1);
  if (op == 0x66)
    {
      data16 = 1;
      op = read_memory_unsigned_integer (pc + 1, 1);
    }

  switch (op)
    {
    case 0xe9:
      /* Relative jump: if data16 == 0, disp32, else disp16.  */
      if (data16)
	{
	  delta = read_memory_integer (pc + 2, 2);

	  /* Include the size of the jmp instruction (including the
             0x66 prefix).  */
	  delta += 4;
	}
      else
	{
	  delta = read_memory_integer (pc + 1, 4);

	  /* Include the size of the jmp instruction.  */
	  delta += 5;
	}
      break;
    case 0xeb:
      /* Relative jump, disp8 (ignore data16).  */
      delta = read_memory_integer (pc + data16 + 1, 1);

      delta += data16 + 2;
      break;
    }

  return pc + delta;
}