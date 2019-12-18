#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* ulw_prev; struct TYPE_9__* ulw_next; } ;
struct TYPE_8__ {struct TYPE_8__* uln_prev; struct TYPE_8__* uln_next; } ;
struct TYPE_10__ {scalar_t__ ul_numnodes; TYPE_4__* ul_pool; void* ul_next_enc; void* ul_prev_enc; TYPE_2__ ul_null_walk; TYPE_1__ ul_null_node; scalar_t__ ul_debug; } ;
typedef  TYPE_3__ uu_list_t ;
struct TYPE_11__ {int /*<<< orphan*/  ulp_lock; } ;
typedef  TYPE_4__ uu_list_pool_t ;
struct TYPE_12__ {void* ul_next_enc; void* ul_prev_enc; } ;

/* Variables and functions */
 TYPE_7__* UU_LIST_PTR (void*) ; 
 void* UU_PTR_ENCODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_free (TYPE_3__*) ; 
 int /*<<< orphan*/  uu_panic (char*,void*) ; 

void
uu_list_destroy(uu_list_t *lp)
{
	uu_list_pool_t *pp = lp->ul_pool;

	if (lp->ul_debug) {
		if (lp->ul_null_node.uln_next != &lp->ul_null_node ||
		    lp->ul_null_node.uln_prev != &lp->ul_null_node) {
			uu_panic("uu_list_destroy(%p):  list not empty\n",
			    (void *)lp);
		}
		if (lp->ul_numnodes != 0) {
			uu_panic("uu_list_destroy(%p):  numnodes is nonzero, "
			    "but list is empty\n", (void *)lp);
		}
		if (lp->ul_null_walk.ulw_next != &lp->ul_null_walk ||
		    lp->ul_null_walk.ulw_prev != &lp->ul_null_walk) {
			uu_panic("uu_list_destroy(%p):  outstanding walkers\n",
			    (void *)lp);
		}
	}

	(void) pthread_mutex_lock(&pp->ulp_lock);
	UU_LIST_PTR(lp->ul_next_enc)->ul_prev_enc = lp->ul_prev_enc;
	UU_LIST_PTR(lp->ul_prev_enc)->ul_next_enc = lp->ul_next_enc;
	(void) pthread_mutex_unlock(&pp->ulp_lock);
	lp->ul_prev_enc = UU_PTR_ENCODE(NULL);
	lp->ul_next_enc = UU_PTR_ENCODE(NULL);
	lp->ul_pool = NULL;
	uu_free(lp);
}