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
 scalar_t__ TC_HIGH ; 
 scalar_t__ TC_LOW ; 
 scalar_t__ TC_MID ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 

__attribute__((used)) static void sym53c416_set_transfer_counter(int base, unsigned int len)
{
	/* Program Transfer Counter */
	outb(len & 0x0000FF, base + TC_LOW);
	outb((len & 0x00FF00) >> 8, base + TC_MID);
	outb((len & 0xFF0000) >> 16, base + TC_HIGH);
}