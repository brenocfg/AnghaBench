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

/* Variables and functions */
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int safe_rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write32 (int) ; 
 int /*<<< orphan*/  write_op (int,int,int,int) ; 

int main()
{
	int i, op;

	srand(time(0));

	f = fopen("test_misc2.bin", "wb");
	if (!f) return 1;

	write32(0x00ff8000); // stack
	write32(0x300); // IP

	for (i=0x100/4-2; i; i--)
	{
		write32(0x200+i*4); // exception vectors
	}

	for (i=0x100/4; i; i--)
	{
		write32(0); // pad
	}

	for (i=0x100/4; i; i--)
	{
		write32(0x4e734e73); // fill with rte instructions
	}

	for (op = 0; op < 0x10000; op++)
	{
		if ((op&0xf000) == 0x6000) // Bxx
		{
			if ((op&0x00ff) == 0)
				write_op(op, 6, 0, 0);
		}
		else if ((op&0xf0f8)==0x50c8) // DBxx
		{
			write_op(op, 6, 0, 0);
		}
		else if ((op&0xff80)==0x4e80) // Jsr
		{
			int addr = 0x300 + op*8 + 8;
			if ((op&0x3f) == 0x39)
				write_op(op, addr >> 16, addr & 0xffff, 0);
		}
		else if ((op&0xf000)==0xa000 || (op&0xf000)==0xf000) // a-line, f-line
		{
			if (op != 0xa000 && op != 0xf000) continue;
		}
		else if ((op&0xfff8)==0x4e70&&op!=0x4e71&&op!=0x4e76); // rte, rts, stop, reset
		else
		{
			write_op(op, safe_rand(), safe_rand(), safe_rand());
		}
	}

	// jump to the beginning
	write_op(0x4ef8, 0x300, 0x4ef8, 0x300);
	write_op(0x4ef8, 0x300, 0x4ef8, 0x300);

	fclose(f);
	return 0;
}