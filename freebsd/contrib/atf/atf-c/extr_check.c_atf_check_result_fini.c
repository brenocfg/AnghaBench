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
struct TYPE_4__ {TYPE_2__* pimpl; } ;
typedef  TYPE_1__ atf_check_result_t ;
struct TYPE_5__ {int /*<<< orphan*/  m_argv; int /*<<< orphan*/  m_dir; int /*<<< orphan*/  m_stderr; int /*<<< orphan*/  m_stdout; int /*<<< orphan*/  m_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_list_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_status_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_tmpdir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void
atf_check_result_fini(atf_check_result_t *r)
{
    atf_process_status_fini(&r->pimpl->m_status);

    cleanup_tmpdir(&r->pimpl->m_dir, &r->pimpl->m_stdout,
                   &r->pimpl->m_stderr);
    atf_fs_path_fini(&r->pimpl->m_stdout);
    atf_fs_path_fini(&r->pimpl->m_stderr);
    atf_fs_path_fini(&r->pimpl->m_dir);

    atf_list_fini(&r->pimpl->m_argv);

    free(r->pimpl);
}