#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ apr_status_t ;
struct TYPE_5__ {scalar_t__ nidle; scalar_t__ ntotal; int /*<<< orphan*/  avail; int /*<<< orphan*/  listlock; } ;
typedef  TYPE_1__ apr_reslist_t ;
typedef  int /*<<< orphan*/  apr_res_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  apr_thread_cond_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_mutex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ destroy_resource (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_container (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pop_resource (TYPE_1__*) ; 

__attribute__((used)) static apr_status_t reslist_cleanup(void *data_)
{
    apr_status_t rv = APR_SUCCESS;
    apr_reslist_t *rl = data_;
    apr_res_t *res;

#if APR_HAS_THREADS
    apr_thread_mutex_lock(rl->listlock);
#endif

    while (rl->nidle > 0) {
        apr_status_t rv1;
        res = pop_resource(rl);
        rl->ntotal--;
        rv1 = destroy_resource(rl, res);
        if (rv1 != APR_SUCCESS) {
            rv = rv1;  /* loses info in the unlikely event of
                        * multiple *different* failures */
        }
        free_container(rl, res);
    }

    assert(rl->nidle == 0);
    assert(rl->ntotal == 0);

#if APR_HAS_THREADS
    apr_thread_mutex_unlock(rl->listlock);
    apr_thread_mutex_destroy(rl->listlock);
    apr_thread_cond_destroy(rl->avail);
#endif

    return rv;
}