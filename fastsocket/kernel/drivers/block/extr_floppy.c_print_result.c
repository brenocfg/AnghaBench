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
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/ * reply_buffer ; 

__attribute__((used)) static void print_result(char *message, int inr)
{
	int i;

	DPRINT("%s ", message);
	if (inr >= 0)
		for (i = 0; i < inr; i++)
			printk("repl[%d]=%x ", i, reply_buffer[i]);
	printk("\n");
}