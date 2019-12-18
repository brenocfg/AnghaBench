#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int flags; int filedes; int /*<<< orphan*/ * pollset; int /*<<< orphan*/ * pool; int /*<<< orphan*/  ungetchar; int /*<<< orphan*/  blocking; int /*<<< orphan*/  bufsize; scalar_t__ buffer; scalar_t__ buffered; scalar_t__ thlock; int /*<<< orphan*/  fname; } ;
typedef  TYPE_1__ apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EINVAL ; 
 int APR_FOPEN_NOCLEANUP ; 
 int APR_INHERIT ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  APR_THREAD_MUTEX_DEFAULT ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_CLOEXEC ; 
 scalar_t__ apr_palloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_thread_mutex_create (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_unix_child_file_cleanup ; 
 int /*<<< orphan*/  apr_unix_file_cleanup ; 
 int dup (int) ; 
 int dup2 (int,int) ; 
 int dup3 (int,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static apr_status_t file_dup(apr_file_t **new_file, 
                             apr_file_t *old_file, apr_pool_t *p,
                             int which_dup)
{
    int rv;
#ifdef HAVE_DUP3
    int flags = 0;
#endif

    if (which_dup == 2) {
        if ((*new_file) == NULL) {
            /* We can't dup2 unless we have a valid new_file */
            return APR_EINVAL;
        }
#ifdef HAVE_DUP3
        if (!((*new_file)->flags & (APR_FOPEN_NOCLEANUP|APR_INHERIT)))
            flags |= O_CLOEXEC;
        rv = dup3(old_file->filedes, (*new_file)->filedes, flags);
#else
        rv = dup2(old_file->filedes, (*new_file)->filedes);
        if (!((*new_file)->flags & (APR_FOPEN_NOCLEANUP|APR_INHERIT))) {
            int flags;

            if (rv == -1)
                return errno;

            if ((flags = fcntl((*new_file)->filedes, F_GETFD)) == -1)
                return errno;

            flags |= FD_CLOEXEC;
            if (fcntl((*new_file)->filedes, F_SETFD, flags) == -1)
                return errno;

        }
#endif
    } else {
        rv = dup(old_file->filedes);
    }

    if (rv == -1)
        return errno;
    
    if (which_dup == 1) {
        (*new_file) = (apr_file_t *)apr_pcalloc(p, sizeof(apr_file_t));
        (*new_file)->pool = p;
        (*new_file)->filedes = rv;
    }

    (*new_file)->fname = apr_pstrdup(p, old_file->fname);
    (*new_file)->buffered = old_file->buffered;

    /* If the existing socket in a dup2 is already buffered, we
     * have an existing and valid (hopefully) mutex, so we don't
     * want to create it again as we could leak!
     */
#if APR_HAS_THREADS
    if ((*new_file)->buffered && !(*new_file)->thlock && old_file->thlock) {
        apr_thread_mutex_create(&((*new_file)->thlock),
                                APR_THREAD_MUTEX_DEFAULT, p);
    }
#endif
    /* As above, only create the buffer if we haven't already
     * got one.
     */
    if ((*new_file)->buffered && !(*new_file)->buffer) {
        (*new_file)->buffer = apr_palloc(p, old_file->bufsize);
        (*new_file)->bufsize = old_file->bufsize;
    }

    /* this is the way dup() works */
    (*new_file)->blocking = old_file->blocking; 

    /* make sure unget behavior is consistent */
    (*new_file)->ungetchar = old_file->ungetchar;

    /* apr_file_dup2() retains the original cleanup, reflecting 
     * the existing inherit and nocleanup flags.  This means, 
     * that apr_file_dup2() cannot be called against an apr_file_t
     * already closed with apr_file_close, because the expected
     * cleanup was already killed.
     */
    if (which_dup == 2) {
        return APR_SUCCESS;
    }

    /* apr_file_dup() retains all old_file flags with the exceptions
     * of APR_INHERIT and APR_FOPEN_NOCLEANUP.
     * The user must call apr_file_inherit_set() on the dupped 
     * apr_file_t when desired.
     */
    (*new_file)->flags = old_file->flags
                       & ~(APR_INHERIT | APR_FOPEN_NOCLEANUP);

    apr_pool_cleanup_register((*new_file)->pool, (void *)(*new_file),
                              apr_unix_file_cleanup, 
                              apr_unix_child_file_cleanup);
#ifndef WAITIO_USES_POLL
    /* Start out with no pollset.  apr_wait_for_io_or_timeout() will
     * initialize the pollset if needed.
     */
    (*new_file)->pollset = NULL;
#endif
    return APR_SUCCESS;
}