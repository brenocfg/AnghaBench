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
 int /*<<< orphan*/  flush_icache_range (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 int /*<<< orphan*/  vectors_high () ; 

void set_fiq_handler(void *start, unsigned int length)
{
	memcpy((void *)0xffff001c, start, length);
	flush_icache_range(0xffff001c, 0xffff001c + length);
	if (!vectors_high())
		flush_icache_range(0x1c, 0x1c + length);
}