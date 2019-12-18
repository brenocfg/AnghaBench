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
typedef  scalar_t__ apr_status_t ;
struct TYPE_3__ {int filedes; int flags; int /*<<< orphan*/ * pollset; scalar_t__ thlock; int /*<<< orphan*/  fname; } ;
typedef  TYPE_1__ apr_file_t ;

/* Variables and functions */
 int APR_FOPEN_DELONCLOSE ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_pollset_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_thread_mutex_destroy (scalar_t__) ; 
 scalar_t__ close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t file_cleanup(apr_file_t *file, int is_child)
{
    apr_status_t rv = APR_SUCCESS;
    int fd = file->filedes;

    /* Set file descriptor to -1 before close(), so that there is no
     * chance of returning an already closed FD from apr_os_file_get().
     */
    file->filedes = -1;

    if (close(fd) == 0) {
        /* Only the parent process should delete the file! */
        if (!is_child && (file->flags & APR_FOPEN_DELONCLOSE)) {
            unlink(file->fname);
        }
#if APR_HAS_THREADS
        if (file->thlock) {
            rv = apr_thread_mutex_destroy(file->thlock);
        }
#endif
    }
    else {
        /* Restore, close() was not successful. */
        file->filedes = fd;

        /* Are there any error conditions other than EINTR or EBADF? */
        rv = errno;
    }
#ifndef WAITIO_USES_POLL
    if (file->pollset != NULL) {
        apr_status_t pollset_rv = apr_pollset_destroy(file->pollset);
        /* If the file close failed, return its error value,
         * not apr_pollset_destroy()'s.
         */
        if (rv == APR_SUCCESS) {
            rv = pollset_rv;
        }
    }
#endif /* !WAITIO_USES_POLL */
    return rv;
}