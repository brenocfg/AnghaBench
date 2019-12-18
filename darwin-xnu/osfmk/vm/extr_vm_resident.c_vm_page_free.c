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
struct TYPE_6__ {scalar_t__ vmp_fictitious; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  vm_page_free_prepare (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_release (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_release_fictitious (TYPE_1__*) ; 

void
vm_page_free(
	vm_page_t	mem)
{
	vm_page_free_prepare(mem);

	if (mem->vmp_fictitious) {
		vm_page_release_fictitious(mem);
	} else {
		vm_page_release(mem,
				TRUE); /* page queues are locked */
	}
}