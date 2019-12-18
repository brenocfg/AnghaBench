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
struct vm_struct {unsigned long size; struct vm_struct* next; void* addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IO_SIZE ; 
 unsigned long KMAP_END ; 
 unsigned long KMAP_START ; 
 struct vm_struct* iolist ; 
 int /*<<< orphan*/  kfree (struct vm_struct*) ; 
 struct vm_struct* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vm_struct *get_io_area(unsigned long size)
{
	unsigned long addr;
	struct vm_struct **p, *tmp, *area;

	area = kmalloc(sizeof(*area), GFP_KERNEL);
	if (!area)
		return NULL;
	addr = KMAP_START;
	for (p = &iolist; (tmp = *p) ; p = &tmp->next) {
		if (size + addr < (unsigned long)tmp->addr)
			break;
		if (addr > KMAP_END-size) {
			kfree(area);
			return NULL;
		}
		addr = tmp->size + (unsigned long)tmp->addr;
	}
	area->addr = (void *)addr;
	area->size = size + IO_SIZE;
	area->next = *p;
	*p = area;
	return area;
}