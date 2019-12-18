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
struct params {int m_tcpart; int /*<<< orphan*/  m_tcname; int /*<<< orphan*/  m_resfile; } ;
typedef  int /*<<< orphan*/  atf_tp_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
#define  BODY 129 
#define  CLEANUP 128 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_env_get (char*) ; 
 int /*<<< orphan*/  atf_env_has (char*) ; 
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  atf_tp_cleanup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tp_has_tc (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tp_run (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_warning (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usage_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
atf_error_t
run_tc(const atf_tp_t *tp, struct params *p, int *exitcode)
{
    atf_error_t err;

    err = atf_no_error();

    if (!atf_tp_has_tc(tp, p->m_tcname)) {
        err = usage_error("Unknown test case `%s'", p->m_tcname);
        goto out;
    }

    if (!atf_env_has("__RUNNING_INSIDE_ATF_RUN") || strcmp(atf_env_get(
        "__RUNNING_INSIDE_ATF_RUN"), "internal-yes-value") != 0)
    {
        print_warning("Running test cases outside of kyua(1) is unsupported");
        print_warning("No isolation nor timeout control is being applied; you "
                      "may get unexpected failures; see atf-test-case(4)");
    }

    switch (p->m_tcpart) {
    case BODY:
        err = atf_tp_run(tp, p->m_tcname, atf_fs_path_cstring(&p->m_resfile));
        if (atf_is_error(err)) {
            /* TODO: Handle error */
            *exitcode = EXIT_FAILURE;
            atf_error_free(err);
        } else {
            *exitcode = EXIT_SUCCESS;
        }

        break;

    case CLEANUP:
        err = atf_tp_cleanup(tp, p->m_tcname);
        if (atf_is_error(err)) {
            /* TODO: Handle error */
            *exitcode = EXIT_FAILURE;
            atf_error_free(err);
        } else {
            *exitcode = EXIT_SUCCESS;
        }

        break;

    default:
        UNREACHABLE;
    }

    INV(!atf_is_error(err));
out:
    return err;
}