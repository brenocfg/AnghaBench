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
struct vm_area_struct {struct anon_vma* anon_vma; } ;
struct anon_vma_chain {int dummy; } ;
struct anon_vma {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct anon_vma* anon_vma_alloc () ; 
 struct anon_vma_chain* anon_vma_chain_alloc () ; 
 int /*<<< orphan*/  anon_vma_chain_link (struct vm_area_struct*,struct anon_vma_chain*,struct anon_vma*) ; 
 scalar_t__ anon_vma_clone (struct vm_area_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  anon_vma_free (struct anon_vma*) ; 
 int /*<<< orphan*/  get_anon_vma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_anon_vmas (struct vm_area_struct*) ; 

int anon_vma_fork(struct vm_area_struct *vma, struct vm_area_struct *pvma)
{
	struct anon_vma_chain *avc;
	struct anon_vma *anon_vma;

	/* Don't bother if the parent process has no anon_vma here. */
	if (!pvma->anon_vma)
		return 0;

	/*
	 * First, attach the new VMA to the parent VMA's anon_vmas,
	 * so rmap can find non-COWed pages in child processes.
	 */
	if (anon_vma_clone(vma, pvma))
		return -ENOMEM;

	/* Then add our own anon_vma. */
	anon_vma = anon_vma_alloc();
	if (!anon_vma)
		goto out_error;
	avc = anon_vma_chain_alloc();
	if (!avc)
		goto out_error_free_anon_vma;

	anon_vma->root = pvma->anon_vma->root;
	/*
	 * With KSM refcounts, an anon_vma can stay around longer than the
	 * process it belongs to.  The root anon_vma needs to be pinned
	 * until this anon_vma is freed, because that is where the lock lives.
	 */
	get_anon_vma(anon_vma->root);
	/* Mark this anon_vma as the one where our new (COWed) pages go. */
	vma->anon_vma = anon_vma;
	anon_vma_chain_link(vma, avc, anon_vma);

	return 0;

 out_error_free_anon_vma:
	anon_vma_free(anon_vma);
 out_error:
	unlink_anon_vmas(vma);
	return -ENOMEM;
}