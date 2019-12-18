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
struct vm_struct {void* addr; int /*<<< orphan*/  size; struct vm_struct* next; } ;

/* Variables and functions */
 unsigned long IO_SIZE ; 
 int /*<<< orphan*/  __iounmap (void*,int /*<<< orphan*/ ) ; 
 struct vm_struct* iolist ; 
 int /*<<< orphan*/  kfree (struct vm_struct*) ; 

__attribute__((used)) static inline void free_io_area(void *addr)
{
	struct vm_struct **p, *tmp;

	if (!addr)
		return;
	addr = (void *)((unsigned long)addr & -IO_SIZE);
	for (p = &iolist ; (tmp = *p) ; p = &tmp->next) {
		if (tmp->addr == addr) {
			*p = tmp->next;
			__iounmap(tmp->addr, tmp->size);
			kfree(tmp);
			return;
		}
	}
}