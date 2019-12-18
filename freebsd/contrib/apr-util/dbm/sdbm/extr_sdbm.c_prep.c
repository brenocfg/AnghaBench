#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  apr_status_t ;
struct TYPE_9__ {int flags; int /*<<< orphan*/ * pagf; int /*<<< orphan*/ * dirf; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ apr_sdbm_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int32_t ;
typedef  int /*<<< orphan*/  apr_fileperms_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FLOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  APR_FLOCK_SHARED ; 
 int APR_FOPEN_BINARY ; 
 int APR_FOPEN_READ ; 
 int APR_FOPEN_SHARELOCK ; 
 int APR_FOPEN_WRITE ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 int SDBM_RDONLY ; 
 int SDBM_SHARED ; 
 int /*<<< orphan*/  apr_file_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_sdbm_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_sdbm_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  database_cleanup ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static apr_status_t prep(apr_sdbm_t **pdb, const char *dirname, const char *pagname,
                         apr_int32_t flags, apr_fileperms_t perms, apr_pool_t *p)
{
    apr_sdbm_t *db;
    apr_status_t status;

    *pdb = NULL;

    db = malloc(sizeof(*db));
    memset(db, 0, sizeof(*db));

    db->pool = p;

    /*
     * adjust user flags so that WRONLY becomes RDWR, 
     * as required by this package. Also set our internal
     * flag for RDONLY if needed.
     */
    if (!(flags & APR_FOPEN_WRITE)) {
        db->flags |= SDBM_RDONLY;
    }

    /*
     * adjust the file open flags so that we handle locking
     * on our own (don't rely on any locking behavior within
     * an apr_file_t, in case it's ever introduced, and set
     * our own flag.
     */
    if (flags & APR_FOPEN_SHARELOCK) {
        db->flags |= SDBM_SHARED;
        flags &= ~APR_FOPEN_SHARELOCK;
    }

    flags |= APR_FOPEN_BINARY | APR_FOPEN_READ;

    /*
     * open the files in sequence, and stat the dirfile.
     * If we fail anywhere, undo everything, return NULL.
     */

    if ((status = apr_file_open(&db->dirf, dirname, flags, perms, p))
                != APR_SUCCESS)
        goto error;

    if ((status = apr_file_open(&db->pagf, pagname, flags, perms, p))
                != APR_SUCCESS)
        goto error;

    if ((status = apr_sdbm_lock(db, (db->flags & SDBM_RDONLY) 
                                        ? APR_FLOCK_SHARED
                                        : APR_FLOCK_EXCLUSIVE))
                != APR_SUCCESS)
        goto error;

    /* apr_pcalloc zeroed the buffers
     * apr_sdbm_lock stated the dirf->size and invalidated the cache
     */

    /*
     * if we are opened in SHARED mode, unlock ourself 
     */
    if (db->flags & SDBM_SHARED)
        if ((status = apr_sdbm_unlock(db)) != APR_SUCCESS)
            goto error;

    /* make sure that we close the database at some point */
    apr_pool_cleanup_register(p, db, database_cleanup, apr_pool_cleanup_null);

    /* Done! */
    *pdb = db;
    return APR_SUCCESS;

error:
    if (db->dirf && db->pagf)
        (void) apr_sdbm_unlock(db);
    if (db->dirf != NULL)
        (void) apr_file_close(db->dirf);
    if (db->pagf != NULL) {
        (void) apr_file_close(db->pagf);
    }
    free(db);
    return status;
}