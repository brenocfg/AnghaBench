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
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int PAGE_SIZE ; 
 void* diag204_buf ; 
 int diag204_buf_pages ; 
 int /*<<< orphan*/  diag204_buf_vmalloc ; 
 void* page_align_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int) ; 

__attribute__((used)) static void *diag204_alloc_vbuf(int pages)
{
	/* The buffer has to be page aligned! */
	diag204_buf_vmalloc = vmalloc(PAGE_SIZE * (pages + 1));
	if (!diag204_buf_vmalloc)
		return ERR_PTR(-ENOMEM);
	diag204_buf = page_align_ptr(diag204_buf_vmalloc);
	diag204_buf_pages = pages;
	return diag204_buf;
}