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
struct vm_area_struct {int /*<<< orphan*/  anon_vma_chain; } ;
struct anon_vma_chain {int /*<<< orphan*/  same_anon_vma; int /*<<< orphan*/  same_vma; struct anon_vma* anon_vma; struct vm_area_struct* vma; } ;
struct anon_vma {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  anon_vma_lock (struct anon_vma*) ; 
 int /*<<< orphan*/  anon_vma_unlock (struct anon_vma*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void anon_vma_chain_link(struct vm_area_struct *vma,
				struct anon_vma_chain *avc,
				struct anon_vma *anon_vma)
{
	avc->vma = vma;
	avc->anon_vma = anon_vma;
	list_add(&avc->same_vma, &vma->anon_vma_chain);

	anon_vma_lock(anon_vma);
	/*
	 * It's critical to add new vmas to the tail of the anon_vma,
	 * see comment in huge_memory.c:__split_huge_page().
	 */
	list_add_tail(&avc->same_anon_vma, &anon_vma->head);
	anon_vma_unlock(anon_vma);
}