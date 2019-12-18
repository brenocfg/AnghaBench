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
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_error_is (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atf_fs_access_f ; 
 int /*<<< orphan*/  atf_fs_eaccess (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_libc_error_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_no_error () ; 

atf_error_t
atf_fs_exists(const atf_fs_path_t *p, bool *b)
{
    atf_error_t err;

    err = atf_fs_eaccess(p, atf_fs_access_f);
    if (atf_is_error(err)) {
        if (atf_error_is(err, "libc") && atf_libc_error_code(err) == ENOENT) {
            atf_error_free(err);
            err = atf_no_error();
            *b = false;
        }
    } else
        *b = true;

    return err;
}