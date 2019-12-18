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
 void* l2_sram_alloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int,size_t) ; 

void *l2_sram_zalloc(size_t size)
{
	void *addr = l2_sram_alloc(size);

	if (addr)
		memset(addr, 0x00, size);

	return addr;
}