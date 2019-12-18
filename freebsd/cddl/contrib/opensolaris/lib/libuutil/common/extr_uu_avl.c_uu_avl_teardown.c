#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ua_pool; int /*<<< orphan*/  ua_tree; } ;
typedef  TYPE_1__ uu_avl_t ;
typedef  int /*<<< orphan*/  uu_avl_pool_t ;

/* Variables and functions */
 uintptr_t* NODE_ARRAY (int /*<<< orphan*/ *,void*) ; 
 uintptr_t POOL_TO_MARKER (int /*<<< orphan*/ *) ; 
 void* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 

void *
uu_avl_teardown(uu_avl_t *ap, void **cookie)
{
	void *elem = avl_destroy_nodes(&ap->ua_tree, cookie);

	if (elem != NULL) {
		uu_avl_pool_t *pp = ap->ua_pool;
		uintptr_t *na = NODE_ARRAY(pp, elem);

		na[0] = POOL_TO_MARKER(pp);
		na[1] = 0;
	}
	return (elem);
}