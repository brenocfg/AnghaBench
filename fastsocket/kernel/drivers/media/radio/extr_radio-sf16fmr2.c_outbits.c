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
 int /*<<< orphan*/  wait (int,int) ; 

__attribute__((used)) static void outbits(int bits, unsigned int data, int nWait, int io)
{
	int bit;

	for (; --bits >= 0;) {
		bit = (data >> bits) & 1;
		outb(bit, io);
		wait(nWait, io);
		outb(bit | 2, io);
		wait(nWait, io);
		outb(bit, io);
		wait(nWait, io);
	}
}