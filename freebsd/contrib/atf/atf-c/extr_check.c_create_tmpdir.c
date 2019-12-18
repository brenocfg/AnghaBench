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
 int /*<<< orphan*/  atf_env_get_with_default (char*,char*) ; 
 int /*<<< orphan*/  atf_fs_mkdtemp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
atf_error_t
create_tmpdir(atf_fs_path_t *dir)
{
    atf_error_t err;

    err = atf_fs_path_init_fmt(dir, "%s/check.XXXXXX",
                               atf_env_get_with_default("TMPDIR", "/tmp"));
    if (atf_is_error(err))
        goto out;

    err = atf_fs_mkdtemp(dir);
    if (atf_is_error(err)) {
        atf_fs_path_fini(dir);
        goto out;
    }

    INV(!atf_is_error(err));
out:
    return err;
}