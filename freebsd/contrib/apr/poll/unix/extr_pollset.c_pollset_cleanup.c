#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ ** wakeup_pipe; TYPE_1__* provider; } ;
typedef  TYPE_2__ apr_pollset_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int APR_POLLSET_WAKEABLE ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  apr_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_file_socket_pipe_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static apr_status_t pollset_cleanup(void *p)
{
    apr_pollset_t *pollset = (apr_pollset_t *) p;
    if (pollset->provider->cleanup) {
        (*pollset->provider->cleanup)(pollset);
    }
    if (pollset->flags & APR_POLLSET_WAKEABLE) {
        /* Close both sides of the wakeup pipe */
        if (pollset->wakeup_pipe[0]) {
#if APR_FILES_AS_SOCKETS
            apr_file_close(pollset->wakeup_pipe[0]);
#else
            apr_file_socket_pipe_close(pollset->wakeup_pipe[0]);
#endif
            pollset->wakeup_pipe[0] = NULL;
        }
        if (pollset->wakeup_pipe[1]) {
#if APR_FILES_AS_SOCKETS
            apr_file_close(pollset->wakeup_pipe[1]);
#else
            apr_file_socket_pipe_close(pollset->wakeup_pipe[1]);
#endif
            pollset->wakeup_pipe[1] = NULL;
        }
    }

    return APR_SUCCESS;
}