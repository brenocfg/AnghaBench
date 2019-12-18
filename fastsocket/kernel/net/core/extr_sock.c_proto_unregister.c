#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proto {TYPE_2__* twsk_prot; TYPE_1__* rsk_prot; int /*<<< orphan*/ * slab; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {int /*<<< orphan*/ * twsk_slab; int /*<<< orphan*/  twsk_slab_name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * slab; int /*<<< orphan*/  slab_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_list_lock ; 
 int /*<<< orphan*/  release_proto_idx (struct proto*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void proto_unregister(struct proto *prot)
{
	write_lock(&proto_list_lock);
	release_proto_idx(prot);
	list_del(&prot->node);
	write_unlock(&proto_list_lock);

	if (prot->slab != NULL) {
		kmem_cache_destroy(prot->slab);
		prot->slab = NULL;
	}

	if (prot->rsk_prot != NULL && prot->rsk_prot->slab != NULL) {
		kmem_cache_destroy(prot->rsk_prot->slab);
		kfree(prot->rsk_prot->slab_name);
		prot->rsk_prot->slab = NULL;
	}

	if (prot->twsk_prot != NULL && prot->twsk_prot->twsk_slab != NULL) {
		kmem_cache_destroy(prot->twsk_prot->twsk_slab);
		kfree(prot->twsk_prot->twsk_slab_name);
		prot->twsk_prot->twsk_slab = NULL;
	}
}