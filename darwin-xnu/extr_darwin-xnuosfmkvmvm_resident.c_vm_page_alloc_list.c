#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {struct TYPE_6__* vmp_snext; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int KMA_LOMEM ; 
 TYPE_1__* VM_PAGE_NULL ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vm_page_free_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_page_grablo () ; 

kern_return_t
vm_page_alloc_list(
	int	page_count,
	int	flags,
	vm_page_t *list)
{
	vm_page_t	lo_page_list = VM_PAGE_NULL;
	vm_page_t	mem;
	int		i;

	if ( !(flags & KMA_LOMEM))
		panic("vm_page_alloc_list: called w/o KMA_LOMEM");

	for (i = 0; i < page_count; i++) {

		mem = vm_page_grablo();

		if (mem == VM_PAGE_NULL) {
			if (lo_page_list)
				vm_page_free_list(lo_page_list, FALSE);

			*list = VM_PAGE_NULL;

			return (KERN_RESOURCE_SHORTAGE);
		}
		mem->vmp_snext = lo_page_list;
		lo_page_list = mem;
	}
	*list = lo_page_list;

	return (KERN_SUCCESS);
}