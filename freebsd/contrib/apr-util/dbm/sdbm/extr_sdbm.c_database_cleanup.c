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
struct TYPE_3__ {int flags; int /*<<< orphan*/  pagf; int /*<<< orphan*/  dirf; } ;
typedef  TYPE_1__ apr_sdbm_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int SDBM_EXCLUSIVE_LOCK ; 
 int SDBM_SHARED_LOCK ; 
 int /*<<< orphan*/  apr_file_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_file_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static apr_status_t database_cleanup(void *data)
{
    apr_sdbm_t *db = data;

    /*
     * Can't rely on apr_sdbm_unlock, since it will merely
     * decrement the refcnt if several locks are held.
     */
    if (db->flags & (SDBM_SHARED_LOCK | SDBM_EXCLUSIVE_LOCK))
        (void) apr_file_unlock(db->dirf);
    (void) apr_file_close(db->dirf);
    (void) apr_file_close(db->pagf);
    free(db);

    return APR_SUCCESS;
}