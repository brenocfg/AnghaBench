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
struct TYPE_4__ {int /*<<< orphan*/  ua_tree; int /*<<< orphan*/  ua_index; int /*<<< orphan*/ * ua_pool; scalar_t__ ua_debug; } ;
typedef  TYPE_1__ uu_avl_t ;
typedef  int /*<<< orphan*/  uu_avl_pool_t ;
typedef  scalar_t__ uu_avl_index_t ;

/* Variables and functions */
 scalar_t__ INDEX_CHECK (scalar_t__) ; 
 int /*<<< orphan*/  INDEX_DECODE (scalar_t__) ; 
 int /*<<< orphan*/  INDEX_NEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEX_VALID (TYPE_1__*,scalar_t__) ; 
 uintptr_t* NODE_ARRAY (int /*<<< orphan*/ *,void*) ; 
 uintptr_t POOL_TO_MARKER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_panic (char*,void*,void*,void*,...) ; 

void
uu_avl_insert(uu_avl_t *ap, void *elem, uu_avl_index_t idx)
{
	if (ap->ua_debug) {
		uu_avl_pool_t *pp = ap->ua_pool;
		uintptr_t *na = NODE_ARRAY(pp, elem);

		if (na[1] != 0)
			uu_panic("uu_avl_insert(%p, %p, %p): node already "
			    "in tree, or corrupt\n",
			    (void *)ap, elem, (void *)idx);
		if (na[0] == 0)
			uu_panic("uu_avl_insert(%p, %p, %p): node not "
			    "initialized\n",
			    (void *)ap, elem, (void *)idx);
		if (na[0] != POOL_TO_MARKER(pp))
			uu_panic("uu_avl_insert(%p, %p, %p): node from "
			    "other pool, or corrupt\n",
			    (void *)ap, elem, (void *)idx);

		if (!INDEX_VALID(ap, idx))
			uu_panic("uu_avl_insert(%p, %p, %p): %s\n",
			    (void *)ap, elem, (void *)idx,
			    INDEX_CHECK(idx)? "outdated index" :
			    "invalid index");

		/*
		 * invalidate outstanding uu_avl_index_ts.
		 */
		ap->ua_index = INDEX_NEXT(ap->ua_index);
	}
	avl_insert(&ap->ua_tree, elem, INDEX_DECODE(idx));
}