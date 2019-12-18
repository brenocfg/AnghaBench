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
typedef  int /*<<< orphan*/  u8_t ;
struct mem {size_t next; scalar_t__ used; int prev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ram_block ; 
 scalar_t__ ram_end ; 
 struct mem* ram_free ; 

__attribute__((used)) static void plug_holes(struct mem *rmem)
{
	struct mem *nmem;
	struct mem *pmem;

	nmem = (struct mem*)&ram_block[rmem->next];
	if(rmem!=nmem && nmem->used==0 && (u8_t*)nmem!=(u8_t*)ram_end) {
		if(ram_free==nmem) ram_free = rmem;

		rmem->next = nmem->next;
		((struct mem*)&ram_block[nmem->next])->prev = (u8_t*)rmem -	ram_block;
	}

	pmem = (struct mem*)&ram_block[rmem->prev];
	if(pmem!=rmem && pmem->used==0) {
		if(ram_free==rmem) ram_free = pmem;
		pmem->next = rmem->next;
		((struct mem*)&ram_block[rmem->next])->prev = (u8_t*)pmem - ram_block;
	}
}