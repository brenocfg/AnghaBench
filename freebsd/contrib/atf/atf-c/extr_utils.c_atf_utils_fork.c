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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_utils_redirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  init_out_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

pid_t
atf_utils_fork(void)
{
    const pid_t pid = fork();
    if (pid == -1)
        atf_tc_fail("fork failed");

    if (pid == 0) {
        atf_dynstr_t out_name;
        init_out_filename(&out_name, getpid(), "out", false);

        atf_dynstr_t err_name;
        init_out_filename(&err_name, getpid(), "err", false);

        atf_utils_redirect(STDOUT_FILENO, atf_dynstr_cstring(&out_name));
        atf_utils_redirect(STDERR_FILENO, atf_dynstr_cstring(&err_name));

        atf_dynstr_fini(&err_name);
        atf_dynstr_fini(&out_name);
    }
    return pid;
}