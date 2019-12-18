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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ clk ; 
 int inb (int /*<<< orphan*/ ) ; 
 int mo_st ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ power ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int get_tune(u16 io)
{
	outb(power+clk,io);
	udelay(4);

	return !(inb(io) & mo_st);
}