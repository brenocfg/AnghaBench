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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  UIP_MEMCPY (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memr_free (void*) ; 
 void* memr_malloc (int /*<<< orphan*/ ) ; 
 void* memr_realloc (void*,int /*<<< orphan*/ ) ; 

void* memr_reallocm(void *ptr,u32 newsize)
{
	void *nmem;

	nmem = memr_malloc(newsize);
	if(nmem==NULL) return memr_realloc(ptr,newsize);

	UIP_MEMCPY(nmem,ptr,newsize);
	memr_free(ptr);

	return nmem;
}