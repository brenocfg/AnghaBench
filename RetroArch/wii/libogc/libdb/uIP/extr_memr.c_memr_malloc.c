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
typedef  void u8_t ;
typedef  scalar_t__ u32 ;
struct mem {scalar_t__ next; int used; scalar_t__ prev; } ;

/* Variables and functions */
 scalar_t__ MEM_ALIGNMENT ; 
 scalar_t__ SIZEOF_STRUCT_MEM ; 
 scalar_t__ UIP_MEM_SIZE ; 
 void* ram_block ; 
 struct mem* ram_end ; 
 struct mem* ram_free ; 

void* memr_malloc(u32 size)
{
	u32 ptr,ptr2;
	struct mem *rmem,*rmem2;

	if(size==0) return NULL;

	if(size%MEM_ALIGNMENT) size += MEM_ALIGNMENT - ((size+SIZEOF_STRUCT_MEM)%SIZEOF_STRUCT_MEM);
	if(size>UIP_MEM_SIZE) return NULL;

	for(ptr = (u8_t*)ram_free - ram_block;ptr<UIP_MEM_SIZE;ptr=((struct mem*)&ram_block[ptr])->next) {
		rmem = (struct mem*)&ram_block[ptr];
		if(!rmem->used && rmem->next - (ptr + SIZEOF_STRUCT_MEM)>=size + SIZEOF_STRUCT_MEM) {
			ptr2 = ptr + SIZEOF_STRUCT_MEM + size;
			rmem2 = (struct mem*)&ram_block[ptr2];

			rmem2->prev = ptr;
			rmem2->next = rmem->next;
			rmem->next = ptr2;
			if(rmem->next!=UIP_MEM_SIZE) ((struct mem*)&ram_block[rmem2->next])->prev = ptr2;

			rmem2->used = 0;
			rmem->used = 1;

			if(rmem==ram_free) {
				while(ram_free->used && ram_free!=ram_end) ram_free = (struct mem*)&ram_block[ram_free->next];
			}

			return (u8_t*)rmem+SIZEOF_STRUCT_MEM;
		}
	}
	return NULL;
}