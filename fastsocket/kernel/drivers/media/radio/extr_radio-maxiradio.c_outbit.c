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
 int clk ; 
 int data ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int power ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wren ; 

__attribute__((used)) static void outbit(unsigned long bit, u16 io)
{
	int val = power | wren | (bit ? data : 0);

	outb(val, io);
	udelay(4);
	outb(val | clk, io);
	udelay(4);
	outb(val, io);
	udelay(4);
}