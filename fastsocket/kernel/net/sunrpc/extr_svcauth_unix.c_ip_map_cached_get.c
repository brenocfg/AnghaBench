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
struct svc_xprt {int /*<<< orphan*/  xpt_lock; struct ip_map* xpt_auth_cache; int /*<<< orphan*/  xpt_flags; } ;
struct ip_map {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPT_CACHE_AUTH ; 
 int /*<<< orphan*/  cache_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_map_cache ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct ip_map *
ip_map_cached_get(struct svc_xprt *xprt)
{
	struct ip_map *ipm = NULL;

	if (test_bit(XPT_CACHE_AUTH, &xprt->xpt_flags)) {
		spin_lock(&xprt->xpt_lock);
		ipm = xprt->xpt_auth_cache;
		if (ipm != NULL) {
			if (!cache_valid(&ipm->h)) {
				/*
				 * The entry has been invalidated since it was
				 * remembered, e.g. by a second mount from the
				 * same IP address.
				 */
				xprt->xpt_auth_cache = NULL;
				spin_unlock(&xprt->xpt_lock);
				cache_put(&ipm->h, &ip_map_cache);
				return NULL;
			}
			cache_get(&ipm->h);
		}
		spin_unlock(&xprt->xpt_lock);
	}
	return ipm;
}