#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ ENOTEMPTY ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_libc_error (scalar_t__,char*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 scalar_t__ errno ; 
 scalar_t__ rmdir (int /*<<< orphan*/ ) ; 

atf_error_t
atf_fs_rmdir(const atf_fs_path_t *p)
{
    atf_error_t err;

    if (rmdir(atf_fs_path_cstring(p))) {
        if (errno == EEXIST) {
            /* Some operating systems (e.g. OpenSolaris 200906) return
             * EEXIST instead of ENOTEMPTY for non-empty directories.
             * Homogenize the return value so that callers don't need
             * to bother about differences in operating systems. */
            errno = ENOTEMPTY;
        }
        err = atf_libc_error(errno, "Cannot remove directory");
    } else
        err = atf_no_error();

    return err;
}