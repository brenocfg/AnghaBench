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
struct socket {scalar_t__ cache_timestamp; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SO_CACHE_MAX_FREE_BATCH ; 
 scalar_t__ SO_CACHE_TIME_LIMIT ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct socket* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ cached_sock_count ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ net_uptime () ; 
 int /*<<< orphan*/  so_cache_ent ; 
 int /*<<< orphan*/  so_cache_head ; 
 int /*<<< orphan*/  so_cache_max_freed ; 
 int /*<<< orphan*/  so_cache_mtx ; 
 scalar_t__ so_cache_time ; 
 int /*<<< orphan*/  so_cache_timeouts ; 
 int /*<<< orphan*/  so_cache_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct socket*) ; 

boolean_t
so_cache_timer(void)
{
	struct socket	*p;
	int		n_freed = 0;
	boolean_t rc = FALSE;

	lck_mtx_lock(so_cache_mtx);
	so_cache_timeouts++;
	so_cache_time = net_uptime();

	while (!STAILQ_EMPTY(&so_cache_head)) {
		VERIFY(cached_sock_count > 0);
		p = STAILQ_FIRST(&so_cache_head);
		if ((so_cache_time - p->cache_timestamp) <
			SO_CACHE_TIME_LIMIT)
			break;

		STAILQ_REMOVE_HEAD(&so_cache_head, so_cache_ent);
		--cached_sock_count;

		zfree(so_cache_zone, p);

		if (++n_freed >= SO_CACHE_MAX_FREE_BATCH) {
			so_cache_max_freed++;
			break;
		}
	}

	/* Schedule again if there is more to cleanup */
	if (!STAILQ_EMPTY(&so_cache_head))
		rc = TRUE;

	lck_mtx_unlock(so_cache_mtx);
	return (rc);
}