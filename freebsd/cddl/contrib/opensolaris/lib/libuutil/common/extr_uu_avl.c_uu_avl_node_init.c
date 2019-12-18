#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {uintptr_t uap_objsize; uintptr_t uap_nodeoffset; int /*<<< orphan*/  uap_name; scalar_t__ uap_debug; } ;
typedef  TYPE_1__ uu_avl_pool_t ;
typedef  int /*<<< orphan*/  uu_avl_node_t ;

/* Variables and functions */
 uintptr_t POOL_TO_MARKER (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_panic (char*,void*,void*,void*,int /*<<< orphan*/ ,long,long) ; 

void
uu_avl_node_init(void *base, uu_avl_node_t *np, uu_avl_pool_t *pp)
{
	uintptr_t *na = (uintptr_t *)np;

	if (pp->uap_debug) {
		uintptr_t offset = (uintptr_t)np - (uintptr_t)base;
		if (offset + sizeof (*np) > pp->uap_objsize) {
			uu_panic("uu_avl_node_init(%p, %p, %p (\"%s\")): "
			    "offset %ld doesn't fit in object (size %ld)\n",
			    base, (void *)np, (void *)pp, pp->uap_name,
			    (long)offset, (long)pp->uap_objsize);
		}
		if (offset != pp->uap_nodeoffset) {
			uu_panic("uu_avl_node_init(%p, %p, %p (\"%s\")): "
			    "offset %ld doesn't match pool's offset (%ld)\n",
			    base, (void *)np, (void *)pp, pp->uap_name,
			    (long)offset, (long)pp->uap_objsize);
		}
	}

	na[0] = POOL_TO_MARKER(pp);
	na[1] = 0;
}