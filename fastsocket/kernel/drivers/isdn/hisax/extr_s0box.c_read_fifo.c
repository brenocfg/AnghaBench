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
typedef  size_t u_char ;

/* Variables and functions */
 int inb_p (unsigned int) ; 
 int* nibtab ; 
 int /*<<< orphan*/  outb_p (int,unsigned int) ; 

__attribute__((used)) static inline void
read_fifo(unsigned int padr, signed int adr, u_char * data, int size)
{
	int i;
	register u_char n1, n2;
	
	outb_p(0x1c, padr+2);
	outb_p(0x14, padr+2);
	outb_p(adr|0x80, padr);
	outb_p(0x16, padr+2);
	for (i=0; i<size; i++) {
		outb_p(0x17, padr+2);
		n1 = (inb_p(padr+1) >> 3) & 0x17;
		outb_p(0x16,padr+2);
		n2 = (inb_p(padr+1) >> 3) & 0x17;
		*(data++)=nibtab[n1] | (nibtab[n2] << 4);
	}
	outb_p(0x14,padr+2);
	outb_p(0x1c,padr+2);
	return;
}