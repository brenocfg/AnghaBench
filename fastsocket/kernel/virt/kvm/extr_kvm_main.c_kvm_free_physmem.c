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
struct kvm_memslots {int nmemslots; int /*<<< orphan*/ * memslots; } ;
struct kvm {struct kvm_memslots* memslots; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct kvm_memslots*) ; 
 int /*<<< orphan*/  kvm_free_physmem_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void kvm_free_physmem(struct kvm *kvm)
{
	int i;
	struct kvm_memslots *slots = kvm->memslots;

	for (i = 0; i < slots->nmemslots; ++i)
		kvm_free_physmem_slot(&slots->memslots[i], NULL);

	kfree(kvm->memslots);
}