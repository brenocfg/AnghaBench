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
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static u8 read_reg(int reg)
{
	u8 ret = 0;

	inw(reg_base + 1);
	inw(reg_base + 1);
	outb(3, reg_base + 2);
	ret = inb(reg_base + reg);
	outb(0x83, reg_base + 2);

	return ret;
}