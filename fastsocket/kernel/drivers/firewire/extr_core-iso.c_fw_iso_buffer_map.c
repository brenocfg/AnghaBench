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
struct vm_area_struct {unsigned long vm_start; } ;
struct fw_iso_buffer {int page_count; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int vm_insert_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

int fw_iso_buffer_map(struct fw_iso_buffer *buffer, struct vm_area_struct *vma)
{
	unsigned long uaddr;
	int i, err;

	uaddr = vma->vm_start;
	for (i = 0; i < buffer->page_count; i++) {
		err = vm_insert_page(vma, uaddr, buffer->pages[i]);
		if (err)
			return err;

		uaddr += PAGE_SIZE;
	}

	return 0;
}