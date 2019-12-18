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
 int /*<<< orphan*/  WRITE_RWA (int,int) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int inb (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void rwa010_read_ident(void)
{
	unsigned char si[9];
	int i, j;

	WRITE_RWA(3, 0);
	WRITE_RWA(0, 128);

	outb(1, 0x279);

	mdelay(1);

	dprintk("Identifier: ");
	for (i = 0; i < 9; i++) {
		si[i] = 0;
		for (j = 0; j < 8; j++) {
			int bit;
			udelay(250);
			inb(0x203);
			udelay(250);
			bit = inb(0x203);
			dprintk("%02X ", bit);
			bit = (bit == 0xaa) ? 1 : 0;
			si[i] |= bit << j;
		}
		dprintk("(%02X) ", si[i]);
	}
	dprintk("\n");
}