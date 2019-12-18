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
struct fscache_cookie {int /*<<< orphan*/  usage; int /*<<< orphan*/  backing_objects; struct fscache_cookie* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  _debug (char*,struct fscache_cookie*) ; 
 int /*<<< orphan*/  _enter (char*,struct fscache_cookie*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_cookie_jar ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fscache_cookie*) ; 

void __fscache_cookie_put(struct fscache_cookie *cookie)
{
	struct fscache_cookie *parent;

	_enter("%p", cookie);

	for (;;) {
		_debug("FREE COOKIE %p", cookie);
		parent = cookie->parent;
		BUG_ON(!hlist_empty(&cookie->backing_objects));
		kmem_cache_free(fscache_cookie_jar, cookie);

		if (!parent)
			break;

		cookie = parent;
		BUG_ON(atomic_read(&cookie->usage) <= 0);
		if (!atomic_dec_and_test(&cookie->usage))
			break;
	}

	_leave("");
}