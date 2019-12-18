#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_7__ {TYPE_1__* pimpl; } ;
typedef  TYPE_2__ atf_check_result_t ;
struct TYPE_6__ {int /*<<< orphan*/  m_status; int /*<<< orphan*/  m_stderr; int /*<<< orphan*/  m_stdout; } ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  atf_check_result_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  atf_check_result_init (TYPE_2__*,char const* const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_rmdir (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tmpdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fork_and_wait (char const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

atf_error_t
atf_check_exec_array(const char *const *argv, atf_check_result_t *r)
{
    atf_error_t err;
    atf_fs_path_t dir;

    err = create_tmpdir(&dir);
    if (atf_is_error(err))
        goto out;

    err = atf_check_result_init(r, argv, &dir);
    if (atf_is_error(err)) {
        atf_error_t err2 = atf_fs_rmdir(&dir);
        INV(!atf_is_error(err2));
        goto out;
    }

    err = fork_and_wait(argv, &r->pimpl->m_stdout, &r->pimpl->m_stderr,
                        &r->pimpl->m_status);
    if (atf_is_error(err)) {
        atf_check_result_fini(r);
        goto out;
    }

    INV(!atf_is_error(err));

    atf_fs_path_fini(&dir);
out:
    return err;
}