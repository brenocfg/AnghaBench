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
struct TYPE_2__ {int /*<<< orphan*/  pool; int /*<<< orphan*/ * filename; int /*<<< orphan*/  base; int /*<<< orphan*/  shmid; int /*<<< orphan*/  realsize; } ;
typedef  TYPE_1__ apr_shm_t ;

/* Variables and functions */
 scalar_t__ APR_ENOTIMPL ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  IPC_RMID ; 
 scalar_t__ access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_file_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  make_shm_open_safe_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int shm_unlink (int /*<<< orphan*/ ) ; 
 int shmctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int shmdt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static apr_status_t shm_cleanup_owner(void *m_)
{
    apr_shm_t *m = (apr_shm_t *)m_;

    /* anonymous shared memory */
    if (m->filename == NULL) {
#if APR_USE_SHMEM_MMAP_ZERO || APR_USE_SHMEM_MMAP_ANON
        if (munmap(m->base, m->realsize) == -1) {
            return errno;
        }
        return APR_SUCCESS;
#elif APR_USE_SHMEM_SHMGET_ANON
        if (shmdt(m->base) == -1) {
            return errno;
        }
        /* This segment will automatically remove itself after all
         * references have detached. */
        return APR_SUCCESS;
#endif
    }

    /* name-based shared memory */
    else {
#if APR_USE_SHMEM_MMAP_TMP
        if (munmap(m->base, m->realsize) == -1) {
            return errno;
        }
        if (access(m->filename, F_OK)) {
            return APR_SUCCESS;
        }
        else {
            return apr_file_remove(m->filename, m->pool);
        }
#elif APR_USE_SHMEM_MMAP_SHM
        if (munmap(m->base, m->realsize) == -1) {
            return errno;
        }
        if (shm_unlink(make_shm_open_safe_name(m->filename, m->pool)) == -1 && errno != ENOENT) {
            return errno;
        }
        return APR_SUCCESS;
#elif APR_USE_SHMEM_SHMGET
        /* Indicate that the segment is to be destroyed as soon
         * as all processes have detached. This also disallows any
         * new attachments to the segment. */
        if (shmctl(m->shmid, IPC_RMID, NULL) == -1 && errno != EINVAL) {
            return errno;
        }
        if (shmdt(m->base) == -1) {
            return errno;
        }
        if (access(m->filename, F_OK)) {
            return APR_SUCCESS;
        }
        else {
            return apr_file_remove(m->filename, m->pool);
        }
#else
        return APR_ENOTIMPL;
#endif
    }
}