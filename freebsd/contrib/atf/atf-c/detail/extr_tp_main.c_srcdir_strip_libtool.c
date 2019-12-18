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
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  atf_fs_path_branch_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
atf_error_t
srcdir_strip_libtool(atf_fs_path_t *srcdir)
{
    atf_error_t err;
    atf_fs_path_t parent;

    err = atf_fs_path_branch_path(srcdir, &parent);
    if (atf_is_error(err))
        goto out;

    atf_fs_path_fini(srcdir);
    *srcdir = parent;

    INV(!atf_is_error(err));
out:
    return err;
}