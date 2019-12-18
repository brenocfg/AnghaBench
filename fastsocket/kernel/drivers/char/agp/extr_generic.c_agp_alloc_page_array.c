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
struct agp_memory {int vmalloc_flag; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int __GFP_NORETRY ; 
 int /*<<< orphan*/ * kmalloc (size_t,int) ; 
 int /*<<< orphan*/ * vmalloc (size_t) ; 

void agp_alloc_page_array(size_t size, struct agp_memory *mem)
{
	mem->pages = NULL;
	mem->vmalloc_flag = false;

	if (size <= 2*PAGE_SIZE)
		mem->pages = kmalloc(size, GFP_KERNEL | __GFP_NORETRY);
	if (mem->pages == NULL) {
		mem->pages = vmalloc(size);
		mem->vmalloc_flag = true;
	}
}