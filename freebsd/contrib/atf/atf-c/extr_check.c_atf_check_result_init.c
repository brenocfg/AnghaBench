#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct atf_check_result_impl {int dummy; } ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
struct TYPE_4__ {TYPE_2__* pimpl; } ;
typedef  TYPE_1__ atf_check_result_t ;
struct TYPE_5__ {int /*<<< orphan*/  m_argv; int /*<<< orphan*/  m_dir; int /*<<< orphan*/  m_stdout; int /*<<< orphan*/  m_stderr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  array_to_list (char const* const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_no_memory_error () ; 
 TYPE_2__* malloc (int) ; 

__attribute__((used)) static
atf_error_t
atf_check_result_init(atf_check_result_t *r, const char *const *argv,
                      const atf_fs_path_t *dir)
{
    atf_error_t err;

    r->pimpl = malloc(sizeof(struct atf_check_result_impl));
    if (r->pimpl == NULL)
        return atf_no_memory_error();

    err = array_to_list(argv, &r->pimpl->m_argv);
    if (atf_is_error(err))
        goto out;

    err = atf_fs_path_copy(&r->pimpl->m_dir, dir);
    if (atf_is_error(err))
        goto err_argv;

    err = atf_fs_path_init_fmt(&r->pimpl->m_stdout, "%s/stdout",
                               atf_fs_path_cstring(dir));
    if (atf_is_error(err))
        goto err_dir;

    err = atf_fs_path_init_fmt(&r->pimpl->m_stderr, "%s/stderr",
                               atf_fs_path_cstring(dir));
    if (atf_is_error(err))
        goto err_stdout;

    INV(!atf_is_error(err));
    goto out;

err_stdout:
    atf_fs_path_fini(&r->pimpl->m_stdout);
err_dir:
    atf_fs_path_fini(&r->pimpl->m_dir);
err_argv:
    atf_list_fini(&r->pimpl->m_argv);
out:
    return err;
}