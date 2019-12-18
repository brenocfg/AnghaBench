#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* uaw_prev; struct TYPE_7__* uaw_next; } ;
struct TYPE_8__ {int /*<<< orphan*/  ua_tree; TYPE_3__* ua_pool; void* ua_next_enc; void* ua_prev_enc; TYPE_1__ ua_null_walk; scalar_t__ ua_debug; } ;
typedef  TYPE_2__ uu_avl_t ;
struct TYPE_9__ {int /*<<< orphan*/  uap_lock; } ;
typedef  TYPE_3__ uu_avl_pool_t ;
struct TYPE_10__ {void* ua_next_enc; void* ua_prev_enc; } ;

/* Variables and functions */
 TYPE_6__* UU_AVL_PTR (void*) ; 
 void* UU_PTR_ENCODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_free (TYPE_2__*) ; 
 int /*<<< orphan*/  uu_panic (char*,void*) ; 

void
uu_avl_destroy(uu_avl_t *ap)
{
	uu_avl_pool_t *pp = ap->ua_pool;

	if (ap->ua_debug) {
		if (avl_numnodes(&ap->ua_tree) != 0) {
			uu_panic("uu_avl_destroy(%p): tree not empty\n",
			    (void *)ap);
		}
		if (ap->ua_null_walk.uaw_next != &ap->ua_null_walk ||
		    ap->ua_null_walk.uaw_prev != &ap->ua_null_walk) {
			uu_panic("uu_avl_destroy(%p):  outstanding walkers\n",
			    (void *)ap);
		}
	}
	(void) pthread_mutex_lock(&pp->uap_lock);
	UU_AVL_PTR(ap->ua_next_enc)->ua_prev_enc = ap->ua_prev_enc;
	UU_AVL_PTR(ap->ua_prev_enc)->ua_next_enc = ap->ua_next_enc;
	(void) pthread_mutex_unlock(&pp->uap_lock);
	ap->ua_prev_enc = UU_PTR_ENCODE(NULL);
	ap->ua_next_enc = UU_PTR_ENCODE(NULL);

	ap->ua_pool = NULL;
	avl_destroy(&ap->ua_tree);

	uu_free(ap);
}