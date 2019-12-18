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
 unsigned char in_byte () ; 
 int /*<<< orphan*/  out_byte (int) ; 
 int /*<<< orphan*/  start () ; 
 int /*<<< orphan*/  stop () ; 

unsigned char
ds1302_readreg(int reg) 
{
	unsigned char x;

	start();
	out_byte(0x81 | (reg << 1)); /* read register */
	x = in_byte();
	stop();

	return x;
}