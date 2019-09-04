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
struct malloc_header {unsigned long size; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 

void* realloc(void* ptr,size_t nsize)
{
	if (ptr==0){
		return malloc(nsize);
	}
	else if (nsize==0)
		return ptr;
		
	struct malloc_header *bl=ptr-sizeof(struct malloc_header);
	unsigned long size=bl->size;
	void *newptr=malloc(size+nsize);
	memcpy(newptr,ptr,size);
	free(ptr);
	return newptr;
}