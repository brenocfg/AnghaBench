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
struct fscache_cookie {int /*<<< orphan*/  backing_objects; int /*<<< orphan*/  stores_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct fscache_cookie*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void fscache_cookie_init_once(void *_cookie)
{
	struct fscache_cookie *cookie = _cookie;

	memset(cookie, 0, sizeof(*cookie));
	spin_lock_init(&cookie->lock);
	spin_lock_init(&cookie->stores_lock);
	INIT_HLIST_HEAD(&cookie->backing_objects);
}