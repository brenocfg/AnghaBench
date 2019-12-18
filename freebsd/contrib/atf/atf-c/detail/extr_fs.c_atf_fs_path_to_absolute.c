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
 int /*<<< orphan*/  PRE (int) ; 
 int /*<<< orphan*/  atf_fs_getcwd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_append_path (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_is_absolute (int /*<<< orphan*/  const*) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 

atf_error_t
atf_fs_path_to_absolute(const atf_fs_path_t *p, atf_fs_path_t *pa)
{
    atf_error_t err;

    PRE(!atf_fs_path_is_absolute(p));

    err = atf_fs_getcwd(pa);
    if (atf_is_error(err))
        goto out;

    err = atf_fs_path_append_path(pa, p);
    if (atf_is_error(err))
        atf_fs_path_fini(pa);

out:
    return err;
}