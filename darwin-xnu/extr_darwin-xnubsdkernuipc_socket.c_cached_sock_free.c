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
struct socket {int /*<<< orphan*/  cache_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ cached_sock_count ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ max_cached_sock_count ; 
 int /*<<< orphan*/  net_uptime () ; 
 int /*<<< orphan*/  so_cache_ent ; 
 int /*<<< orphan*/  so_cache_head ; 
 scalar_t__ so_cache_hw ; 
 int /*<<< orphan*/  so_cache_mtx ; 
 int /*<<< orphan*/  so_cache_time ; 
 int /*<<< orphan*/  so_cache_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct socket*) ; 

__attribute__((used)) static void
cached_sock_free(struct socket *so)
{

	lck_mtx_lock(so_cache_mtx);

	so_cache_time = net_uptime();
	if (++cached_sock_count > max_cached_sock_count) {
		--cached_sock_count;
		lck_mtx_unlock(so_cache_mtx);
		zfree(so_cache_zone, so);
	} else {
		if (so_cache_hw < cached_sock_count)
			so_cache_hw = cached_sock_count;

		STAILQ_INSERT_TAIL(&so_cache_head, so, so_cache_ent);

		so->cache_timestamp = so_cache_time;
		lck_mtx_unlock(so_cache_mtx);
	}
}