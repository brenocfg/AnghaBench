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

/* Variables and functions */
 scalar_t__ EXIT_SUCCESS ; 
 int /*<<< orphan*/  INV (int) ; 
 scalar_t__ atf_process_status_coredump (int /*<<< orphan*/  const*) ; 
 scalar_t__ atf_process_status_exited (int /*<<< orphan*/  const*) ; 
 int atf_process_status_exitstatus (int /*<<< orphan*/  const*) ; 
 scalar_t__ atf_process_status_signaled (int /*<<< orphan*/  const*) ; 
 int atf_process_status_termsig (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void
update_success_from_status(const char *progname,
                           const atf_process_status_t *status, bool *success)
{
    bool s = atf_process_status_exited(status) &&
             atf_process_status_exitstatus(status) == EXIT_SUCCESS;

    if (atf_process_status_exited(status)) {
        if (atf_process_status_exitstatus(status) == EXIT_SUCCESS)
            INV(s);
        else {
            INV(!s);
            fprintf(stderr, "%s failed with exit code %d\n", progname,
                    atf_process_status_exitstatus(status));
        }
    } else if (atf_process_status_signaled(status)) {
        INV(!s);
        fprintf(stderr, "%s failed due to signal %d%s\n", progname,
                atf_process_status_termsig(status),
                atf_process_status_coredump(status) ? " (core dumped)" : "");
    } else {
        INV(!s);
        fprintf(stderr, "%s failed due to unknown reason\n", progname);
    }

    *success = s;
}