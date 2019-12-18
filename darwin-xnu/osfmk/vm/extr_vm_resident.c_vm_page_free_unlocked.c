#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {scalar_t__ vmp_fictitious; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  vm_page_free_prepare_object (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free_prepare_queues (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lockspin_queues () ; 
 int /*<<< orphan*/  vm_page_release (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_release_fictitious (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unlock_queues () ; 

void
vm_page_free_unlocked(
	vm_page_t	mem,
	boolean_t	remove_from_hash)
{
	vm_page_lockspin_queues();
	vm_page_free_prepare_queues(mem);
	vm_page_unlock_queues();

	vm_page_free_prepare_object(mem, remove_from_hash);

	if (mem->vmp_fictitious) {
		vm_page_release_fictitious(mem);
	} else {
		vm_page_release(mem, FALSE); /* page queues are not locked */
	}
}