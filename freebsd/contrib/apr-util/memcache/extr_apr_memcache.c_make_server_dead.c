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
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_memcache_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  btime; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ apr_memcache_server_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_MC_SERVER_DEAD ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_thread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_time_now () ; 

__attribute__((used)) static apr_status_t make_server_dead(apr_memcache_t *mc, apr_memcache_server_t *ms)
{
#if APR_HAS_THREADS
    apr_thread_mutex_lock(ms->lock);
#endif
    ms->status = APR_MC_SERVER_DEAD;
    ms->btime = apr_time_now();
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(ms->lock);
#endif
    return APR_SUCCESS;
}