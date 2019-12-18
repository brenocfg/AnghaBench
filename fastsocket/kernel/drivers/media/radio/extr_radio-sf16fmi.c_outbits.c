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
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void outbits(int bits, unsigned int data, int io)
{
	while (bits--) {
		if (data & 1) {
			outb(5, io);
			udelay(6);
			outb(7, io);
			udelay(6);
		} else {
			outb(1, io);
			udelay(6);
			outb(3, io);
			udelay(6);
		}
		data >>= 1;
	}
}