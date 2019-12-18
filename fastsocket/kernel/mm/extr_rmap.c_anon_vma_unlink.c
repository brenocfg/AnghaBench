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
struct anon_vma_chain {int /*<<< orphan*/  same_anon_vma; struct anon_vma* anon_vma; } ;
struct anon_vma {struct anon_vma* root; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  anon_vma_free (struct anon_vma*) ; 
 int /*<<< orphan*/  anon_vma_lock (struct anon_vma*) ; 
 int /*<<< orphan*/  anon_vma_unlock (struct anon_vma*) ; 
 int /*<<< orphan*/  anonvma_external_refcount (struct anon_vma*) ; 
 int /*<<< orphan*/  drop_anon_vma (struct anon_vma*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void anon_vma_unlink(struct anon_vma_chain *anon_vma_chain)
{
	struct anon_vma *anon_vma = anon_vma_chain->anon_vma;
	int empty;

	/* If anon_vma_fork fails, we can get an empty anon_vma_chain. */
	if (!anon_vma)
		return;

	anon_vma_lock(anon_vma);
	list_del(&anon_vma_chain->same_anon_vma);

	/* We must garbage collect the anon_vma if it's empty */
	empty = list_empty(&anon_vma->head) && !anonvma_external_refcount(anon_vma);
	anon_vma_unlock(anon_vma);

	if (empty) {
		/* We no longer need the root anon_vma */
		if (anon_vma->root != anon_vma)
			drop_anon_vma(anon_vma->root);
		anon_vma_free(anon_vma);
	}
}