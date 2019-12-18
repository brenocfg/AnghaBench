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
 int /*<<< orphan*/  S_IRWXU ; 
 int /*<<< orphan*/  atf_fs_stat_dir_type ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_umask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_contents (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  current_umask () ; 
 int /*<<< orphan*/  do_mkdtemp (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  invalid_umask_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_contents (int /*<<< orphan*/ *,char*) ; 

atf_error_t
atf_fs_mkdtemp(atf_fs_path_t *p)
{
    atf_error_t err;
    char *buf;

    if (!check_umask(S_IRWXU, S_IRWXU)) {
        err = invalid_umask_error(p, atf_fs_stat_dir_type, current_umask());
        goto out;
    }

    err = copy_contents(p, &buf);
    if (atf_is_error(err))
        goto out;

    err = do_mkdtemp(buf);
    if (atf_is_error(err))
        goto out_buf;

    replace_contents(p, buf);

    INV(!atf_is_error(err));
out_buf:
    free(buf);
out:
    return err;
}