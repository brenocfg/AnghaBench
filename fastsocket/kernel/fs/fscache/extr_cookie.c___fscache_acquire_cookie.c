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
struct fscache_cookie_def {int type; int /*<<< orphan*/ * name; int /*<<< orphan*/  get_key; } ;
struct fscache_cookie {int /*<<< orphan*/  n_children; struct fscache_cookie_def const* def; int /*<<< orphan*/  stores; scalar_t__ flags; void* netfs_data; struct fscache_cookie* parent; int /*<<< orphan*/  usage; int /*<<< orphan*/  n_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  FSCACHE_COOKIE_TYPE_DATAFILE 129 
#define  FSCACHE_COOKIE_TYPE_INDEX 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int __GFP_WAIT ; 
 int /*<<< orphan*/  __fscache_cookie_put (struct fscache_cookie*) ; 
 int /*<<< orphan*/  _enter (char*,char*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ fscache_acquire_non_index_cookie (struct fscache_cookie*) ; 
 int /*<<< orphan*/  fscache_cookie_jar ; 
 int /*<<< orphan*/  fscache_n_acquires ; 
 int /*<<< orphan*/  fscache_n_acquires_nobufs ; 
 int /*<<< orphan*/  fscache_n_acquires_null ; 
 int /*<<< orphan*/  fscache_n_acquires_ok ; 
 int /*<<< orphan*/  fscache_n_acquires_oom ; 
 int /*<<< orphan*/  fscache_n_cookie_data ; 
 int /*<<< orphan*/  fscache_n_cookie_index ; 
 int /*<<< orphan*/  fscache_n_cookie_special ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 struct fscache_cookie* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct fscache_cookie *__fscache_acquire_cookie(
	struct fscache_cookie *parent,
	const struct fscache_cookie_def *def,
	void *netfs_data)
{
	struct fscache_cookie *cookie;

	BUG_ON(!def);

	_enter("{%s},{%s},%p",
	       parent ? (char *) parent->def->name : "<no-parent>",
	       def->name, netfs_data);

	fscache_stat(&fscache_n_acquires);

	/* if there's no parent cookie, then we don't create one here either */
	if (!parent) {
		fscache_stat(&fscache_n_acquires_null);
		_leave(" [no parent]");
		return NULL;
	}

	/* validate the definition */
	BUG_ON(!def->get_key);
	BUG_ON(!def->name[0]);

	BUG_ON(def->type == FSCACHE_COOKIE_TYPE_INDEX &&
	       parent->def->type != FSCACHE_COOKIE_TYPE_INDEX);

	/* allocate and initialise a cookie */
	cookie = kmem_cache_alloc(fscache_cookie_jar, GFP_KERNEL);
	if (!cookie) {
		fscache_stat(&fscache_n_acquires_oom);
		_leave(" [ENOMEM]");
		return NULL;
	}

	atomic_set(&cookie->usage, 1);
	atomic_set(&cookie->n_children, 0);

	/* We keep the active count elevated until relinquishment to prevent an
	 * attempt to wake up every time the object operations queue quiesces.
	 */
	atomic_set(&cookie->n_active, 1);

	atomic_inc(&parent->usage);
	atomic_inc(&parent->n_children);

	cookie->def		= def;
	cookie->parent		= parent;
	cookie->netfs_data	= netfs_data;
	cookie->flags		= 0;

	/* radix tree insertion won't use the preallocation pool unless it's
	 * told it may not wait */
	INIT_RADIX_TREE(&cookie->stores, GFP_NOFS & ~__GFP_WAIT);

	switch (cookie->def->type) {
	case FSCACHE_COOKIE_TYPE_INDEX:
		fscache_stat(&fscache_n_cookie_index);
		break;
	case FSCACHE_COOKIE_TYPE_DATAFILE:
		fscache_stat(&fscache_n_cookie_data);
		break;
	default:
		fscache_stat(&fscache_n_cookie_special);
		break;
	}

	/* if the object is an index then we need do nothing more here - we
	 * create indices on disk when we need them as an index may exist in
	 * multiple caches */
	if (cookie->def->type != FSCACHE_COOKIE_TYPE_INDEX) {
		if (fscache_acquire_non_index_cookie(cookie) < 0) {
			atomic_dec(&parent->n_children);
			__fscache_cookie_put(cookie);
			fscache_stat(&fscache_n_acquires_nobufs);
			_leave(" = NULL");
			return NULL;
		}
	}

	fscache_stat(&fscache_n_acquires_ok);
	_leave(" = %p", cookie);
	return cookie;
}