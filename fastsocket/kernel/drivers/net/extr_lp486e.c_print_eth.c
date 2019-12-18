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
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void print_eth(char *add)
{
	int i;

	printk ("Dest  ");
	for (i = 0; i < 6; i++)
		printk(" %2.2X", (unsigned char) add[i]);
	printk ("\n");

	printk ("Source");
	for (i = 0; i < 6; i++)
		printk(" %2.2X", (unsigned char) add[i+6]);
	printk ("\n");

	printk ("type %2.2X%2.2X\n",
		(unsigned char) add[12], (unsigned char) add[13]);
}