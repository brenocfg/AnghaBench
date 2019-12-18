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
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_error_is (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atf_fs_rmdir (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_fs_unlink (int /*<<< orphan*/  const*) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_libc_error_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
cleanup_tmpdir(const atf_fs_path_t *dir, const atf_fs_path_t *outfile,
               const atf_fs_path_t *errfile)
{
    {
        atf_error_t err = atf_fs_unlink(outfile);
        if (atf_is_error(err)) {
            INV(atf_error_is(err, "libc") &&
                atf_libc_error_code(err) == ENOENT);
            atf_error_free(err);
        } else
            INV(!atf_is_error(err));
    }

    {
        atf_error_t err = atf_fs_unlink(errfile);
        if (atf_is_error(err)) {
            INV(atf_error_is(err, "libc") &&
                atf_libc_error_code(err) == ENOENT);
            atf_error_free(err);
        } else
            INV(!atf_is_error(err));
    }

    {
        atf_error_t err = atf_fs_rmdir(dir);
        INV(!atf_is_error(err));
    }
}