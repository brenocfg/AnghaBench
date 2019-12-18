#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct dirent64 {int dummy; } ;
struct dirent {scalar_t__ DIRENT_INODE; } ;
typedef  scalar_t__ apr_status_t ;
typedef  int apr_int32_t ;
typedef  scalar_t__ apr_ino_t ;
struct TYPE_9__ {int valid; int inode; int /*<<< orphan*/  name; scalar_t__ filetype; int /*<<< orphan*/  pool; int /*<<< orphan*/ * fname; } ;
typedef  TYPE_1__ apr_finfo_t ;
typedef  scalar_t__ apr_filetype_e ;
struct TYPE_10__ {TYPE_3__* entry; int /*<<< orphan*/  pool; int /*<<< orphan*/  dirname; int /*<<< orphan*/  dirstruct; } ;
typedef  TYPE_2__ apr_dir_t ;
struct TYPE_11__ {int DIRENT_INODE; int /*<<< orphan*/  d_name; int /*<<< orphan*/  DIRENT_TYPE; } ;

/* Variables and functions */
 scalar_t__ APR_ENOENT ; 
 int APR_FINFO_INODE ; 
 int APR_FINFO_LINK ; 
 int APR_FINFO_NAME ; 
 int APR_FINFO_TYPE ; 
 scalar_t__ APR_INCOMPLETE ; 
 int APR_PATH_MAX ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ APR_UNKFILE ; 
 scalar_t__ EINVAL ; 
 char* apr_cpystrn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_stat (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ filetype_from_dirent_type (int /*<<< orphan*/ ) ; 
 TYPE_3__* readdir (int /*<<< orphan*/ ) ; 
 scalar_t__ readdir64_r (int /*<<< orphan*/ ,TYPE_3__*,struct dirent64**) ; 
 scalar_t__ readdir_r (int /*<<< orphan*/ ,TYPE_3__*,struct dirent**) ; 

apr_status_t apr_dir_read(apr_finfo_t *finfo, apr_int32_t wanted,
                          apr_dir_t *thedir)
{
    apr_status_t ret = 0;
#ifdef DIRENT_TYPE
    apr_filetype_e type;
#endif
#if APR_HAS_THREADS && defined(_POSIX_THREAD_SAFE_FUNCTIONS) \
                    && !defined(READDIR_IS_THREAD_SAFE)
#ifdef APR_USE_READDIR64_R
    struct dirent64 *retent;

    /* If LFS is enabled and readdir64_r is available, readdir64_r is
     * used in preference to readdir_r.  This allows directories to be
     * read which contain a (64-bit) inode number which doesn't fit
     * into the 32-bit apr_ino_t, iff the caller doesn't actually care
     * about the inode number (i.e. wanted & APR_FINFO_INODE == 0).
     * (such inodes may be seen in some wonky NFS environments)
     *
     * Similarly, if the d_off field cannot be reprented in a 32-bit
     * offset, the libc readdir_r() would barf; using readdir64_r
     * bypasses that case entirely since APR does not care about
     * d_off. */

    ret = readdir64_r(thedir->dirstruct, thedir->entry, &retent);
#else

    struct dirent *retent;

    ret = readdir_r(thedir->dirstruct, thedir->entry, &retent);
#endif

    /* POSIX treats "end of directory" as a non-error case, so ret
     * will be zero and retent will be set to NULL in that case. */
    if (!ret && retent == NULL) {
        ret = APR_ENOENT;
    }

    /* Solaris is a bit strange, if there are no more entries in the
     * directory, it returns EINVAL.  Since this is against POSIX, we
     * hack around the problem here.  EINVAL is possible from other
     * readdir implementations, but only if the result buffer is too small.
     * since we control the size of that buffer, we should never have
     * that problem.
     */
    if (ret == EINVAL) {
        ret = APR_ENOENT;
    }
#else
    /* We're about to call a non-thread-safe readdir() that may
       possibly set `errno', and the logic below actually cares about
       errno after the call.  Therefore we need to clear errno first. */
    errno = 0;
    thedir->entry = readdir(thedir->dirstruct);
    if (thedir->entry == NULL) {
        /* If NULL was returned, this can NEVER be a success. Can it?! */
        if (errno == APR_SUCCESS) {
            ret = APR_ENOENT;
        }
        else
            ret = errno;
    }
#endif

    /* No valid bit flag to test here - do we want one? */
    finfo->fname = NULL;

    if (ret) {
        finfo->valid = 0;
        return ret;
    }

#ifdef DIRENT_TYPE
    type = filetype_from_dirent_type(thedir->entry->DIRENT_TYPE);
    if (type != APR_UNKFILE) {
        wanted &= ~APR_FINFO_TYPE;
    }
#endif
#ifdef DIRENT_INODE
    if (thedir->entry->DIRENT_INODE && thedir->entry->DIRENT_INODE != -1) {
#ifdef APR_USE_READDIR64_R
        /* If readdir64_r is used, check for the overflow case of trying
         * to fit a 64-bit integer into a 32-bit integer. */
        if (sizeof(apr_ino_t) >= sizeof(retent->DIRENT_INODE)
            || (apr_ino_t)retent->DIRENT_INODE == retent->DIRENT_INODE) {
            wanted &= ~APR_FINFO_INODE;
        } else {
            /* Prevent the fallback code below from filling in the
             * inode if the stat call fails. */
            retent->DIRENT_INODE = 0;
        }
#else
        wanted &= ~APR_FINFO_INODE;
#endif /* APR_USE_READDIR64_R */
    }
#endif /* DIRENT_INODE */

    wanted &= ~APR_FINFO_NAME;

    if (wanted)
    {
        char fspec[APR_PATH_MAX];
        char *end;

        end = apr_cpystrn(fspec, thedir->dirname, sizeof fspec);

        if (end > fspec && end[-1] != '/' && (end < fspec + APR_PATH_MAX))
            *end++ = '/';

        apr_cpystrn(end, thedir->entry->d_name, 
                    sizeof fspec - (end - fspec));

        ret = apr_stat(finfo, fspec, APR_FINFO_LINK | wanted, thedir->pool);
        /* We passed a stack name that will disappear */
        finfo->fname = NULL;
    }

    if (wanted && (ret == APR_SUCCESS || ret == APR_INCOMPLETE)) {
        wanted &= ~finfo->valid;
    }
    else {
        /* We don't bail because we fail to stat, when we are only -required-
         * to readdir... but the result will be APR_INCOMPLETE
         */
        finfo->pool = thedir->pool;
        finfo->valid = 0;
#ifdef DIRENT_TYPE
        if (type != APR_UNKFILE) {
            finfo->filetype = type;
            finfo->valid |= APR_FINFO_TYPE;
        }
#endif
#ifdef DIRENT_INODE
        if (thedir->entry->DIRENT_INODE && thedir->entry->DIRENT_INODE != -1) {
            finfo->inode = thedir->entry->DIRENT_INODE;
            finfo->valid |= APR_FINFO_INODE;
        }
#endif
    }

    finfo->name = apr_pstrdup(thedir->pool, thedir->entry->d_name);
    finfo->valid |= APR_FINFO_NAME;

    if (wanted)
        return APR_INCOMPLETE;

    return APR_SUCCESS;
}