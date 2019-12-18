#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ apr_status_t ;
struct TYPE_2__ {scalar_t__ thread_mutex; int /*<<< orphan*/  proc_mutex; } ;
typedef  TYPE_1__ apr_global_mutex_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_proc_mutex_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ apr_thread_mutex_destroy (scalar_t__) ; 

__attribute__((used)) static apr_status_t global_mutex_cleanup(void *data)
{
    apr_global_mutex_t *m = (apr_global_mutex_t *)data;
    apr_status_t rv;

    rv = apr_proc_mutex_destroy(m->proc_mutex);

#if APR_HAS_THREADS
    if (m->thread_mutex) {
        if (rv != APR_SUCCESS) {
            (void)apr_thread_mutex_destroy(m->thread_mutex);
        }
        else {
            rv = apr_thread_mutex_destroy(m->thread_mutex);
        }
    }
#endif /* APR_HAS_THREADS */

    return rv;
}