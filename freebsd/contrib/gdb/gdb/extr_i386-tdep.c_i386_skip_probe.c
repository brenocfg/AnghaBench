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
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  read_memory (scalar_t__,unsigned char*,int) ; 
 unsigned char read_memory_unsigned_integer (scalar_t__,int) ; 

__attribute__((used)) static CORE_ADDR
i386_skip_probe (CORE_ADDR pc)
{
  /* A function may start with

        pushl constant
        call _probe
	addl $4, %esp
	   
     followed by

        pushl %ebp

     etc.  */
  unsigned char buf[8];
  unsigned char op;

  op = read_memory_unsigned_integer (pc, 1);

  if (op == 0x68 || op == 0x6a)
    {
      int delta;

      /* Skip past the `pushl' instruction; it has either a one-byte or a
	 four-byte operand, depending on the opcode.  */
      if (op == 0x68)
	delta = 5;
      else
	delta = 2;

      /* Read the following 8 bytes, which should be `call _probe' (6
	 bytes) followed by `addl $4,%esp' (2 bytes).  */
      read_memory (pc + delta, buf, sizeof (buf));
      if (buf[0] == 0xe8 && buf[6] == 0xc4 && buf[7] == 0x4)
	pc += delta + sizeof (buf);
    }

  return pc;
}