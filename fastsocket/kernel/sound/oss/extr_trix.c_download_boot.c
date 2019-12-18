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
 int /*<<< orphan*/  outb (int,int) ; 
 int* trix_boot ; 
 int trix_boot_len ; 
 int /*<<< orphan*/  trix_write (int,int) ; 

__attribute__((used)) static void download_boot(int base)
{
	int i = 0, n = trix_boot_len;

	if (trix_boot_len == 0)
		return;

	trix_write(0xf8, 0x00);	/* ??????? */
	outb((0x01), base + 6);	/* Clear the internal data pointer */
	outb((0x00), base + 6);	/* Restart */

	/*
	   *  Write the boot code to the RAM upload/download register.
	   *  Each write increments the internal data pointer.
	 */
	outb((0x01), base + 6);	/* Clear the internal data pointer */
	outb((0x1A), 0x390);	/* Select RAM download/upload port */

	for (i = 0; i < n; i++)
		outb((trix_boot[i]), 0x391);
	for (i = n; i < 10016; i++)	/* Clear up to first 16 bytes of data RAM */
		outb((0x00), 0x391);
	outb((0x00), base + 6);	/* Reset */
	outb((0x50), 0x390);	/* ?????? */

}