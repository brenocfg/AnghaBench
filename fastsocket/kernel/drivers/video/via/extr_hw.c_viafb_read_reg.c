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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

u8 viafb_read_reg(int io_port, u8 index)
{
	outb(index, io_port);
	return inb(io_port + 1);
}