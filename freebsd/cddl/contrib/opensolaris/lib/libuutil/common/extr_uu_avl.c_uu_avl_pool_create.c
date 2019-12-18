#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uu_compare_fn_t ;
struct TYPE_7__ {void* ua_prev_enc; void* ua_next_enc; } ;
struct TYPE_6__ {size_t uap_nodeoffset; size_t uap_objsize; int uap_debug; struct TYPE_6__* uap_next; struct TYPE_6__* uap_prev; TYPE_5__ uap_null_avl; int /*<<< orphan*/  uap_lock; scalar_t__ uap_last_index; int /*<<< orphan*/ * uap_cmp; int /*<<< orphan*/  uap_name; } ;
typedef  TYPE_1__ uu_avl_pool_t ;
typedef  int /*<<< orphan*/  uu_avl_node_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int UU_AVL_POOL_DEBUG ; 
 int /*<<< orphan*/  UU_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  UU_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  UU_ERROR_UNKNOWN_FLAG ; 
 int /*<<< orphan*/  UU_NAME_DOMAIN ; 
 void* UU_PTR_ENCODE (TYPE_5__*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  uu_apool_list_lock ; 
 int uu_check_name (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ uu_null_apool ; 
 int /*<<< orphan*/  uu_set_error (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_zalloc (int) ; 

uu_avl_pool_t *
uu_avl_pool_create(const char *name, size_t objsize, size_t nodeoffset,
    uu_compare_fn_t *compare_func, uint32_t flags)
{
	uu_avl_pool_t *pp, *next, *prev;

	if (name == NULL ||
	    uu_check_name(name, UU_NAME_DOMAIN) == -1 ||
	    nodeoffset + sizeof (uu_avl_node_t) > objsize ||
	    compare_func == NULL) {
		uu_set_error(UU_ERROR_INVALID_ARGUMENT);
		return (NULL);
	}

	if (flags & ~UU_AVL_POOL_DEBUG) {
		uu_set_error(UU_ERROR_UNKNOWN_FLAG);
		return (NULL);
	}

	pp = uu_zalloc(sizeof (uu_avl_pool_t));
	if (pp == NULL) {
		uu_set_error(UU_ERROR_NO_MEMORY);
		return (NULL);
	}

	(void) strlcpy(pp->uap_name, name, sizeof (pp->uap_name));
	pp->uap_nodeoffset = nodeoffset;
	pp->uap_objsize = objsize;
	pp->uap_cmp = compare_func;
	if (flags & UU_AVL_POOL_DEBUG)
		pp->uap_debug = 1;
	pp->uap_last_index = 0;

	(void) pthread_mutex_init(&pp->uap_lock, NULL);

	pp->uap_null_avl.ua_next_enc = UU_PTR_ENCODE(&pp->uap_null_avl);
	pp->uap_null_avl.ua_prev_enc = UU_PTR_ENCODE(&pp->uap_null_avl);

	(void) pthread_mutex_lock(&uu_apool_list_lock);
	pp->uap_next = next = &uu_null_apool;
	pp->uap_prev = prev = next->uap_prev;
	next->uap_prev = pp;
	prev->uap_next = pp;
	(void) pthread_mutex_unlock(&uu_apool_list_lock);

	return (pp);
}