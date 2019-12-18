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
typedef  int /*<<< orphan*/  atf_process_status_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_status_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fork_and_wait (char const* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_array (char const* const*,char*) ; 
 int /*<<< orphan*/  update_success_from_status (char const* const,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static
atf_error_t
check_build_run(const char *const *argv, bool *success)
{
    atf_error_t err;
    atf_process_status_t status;

    print_array(argv, ">");

    err = fork_and_wait(argv, NULL, NULL, &status);
    if (atf_is_error(err))
        goto out;

    update_success_from_status(argv[0], &status, success);
    atf_process_status_fini(&status);

    INV(!atf_is_error(err));
out:
    return err;
}