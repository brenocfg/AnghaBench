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
typedef  int u32 ;
struct mem {int next; int prev; scalar_t__ used; } ;

/* Variables and functions */
 int MEM_ALIGNMENT ; 
 int MIN_SIZE ; 
 int SIZEOF_STRUCT_MEM ; 
 int /*<<< orphan*/  UIP_ERROR (char*) ; 
 int UIP_MEM_SIZE ; 
 int /*<<< orphan*/  plug_holes (struct mem*) ; 
 int /*<<< orphan*/ * ram_block ; 
 scalar_t__ ram_end ; 

void* memr_realloc(void *ptr,u32 newsize)
{
	u32 size,ptr1,ptr2;
	struct mem *rmem,*rmem2;

	if(newsize%MEM_ALIGNMENT) newsize += MEM_ALIGNMENT - ((newsize + SIZEOF_STRUCT_MEM)%MEM_ALIGNMENT);
	if(newsize>UIP_MEM_SIZE) return NULL;
	if((u8_t*)ptr<(u8_t*)ram_block || (u8_t*)ptr>=(u8_t*)ram_end) {
		UIP_ERROR("memr_realloc: illegal memory.\n");
		return ptr;
	}
	rmem = (struct mem*)((u8_t*)ptr - SIZEOF_STRUCT_MEM);
	ptr1 = (u8_t*)rmem - ram_block;
	size = rmem->next - ptr1 - SIZEOF_STRUCT_MEM;

	if(newsize+SIZEOF_STRUCT_MEM+MIN_SIZE<size) {
		ptr2 = ptr1 + SIZEOF_STRUCT_MEM + newsize;
		rmem2 = (struct mem*)&ram_block[ptr2];
		rmem2->used = 0;
		rmem2->next = rmem->next;
		rmem2->prev = ptr1;
		rmem->next = ptr2;
		if(rmem2->next!=UIP_MEM_SIZE) ((struct mem*)&ram_block[rmem2->next])->prev = ptr2;

		plug_holes(rmem2);
	}

	return ptr;
}