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

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  check_args (int,char const* const*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const* const,char const* const) ; 
 int h_echo (char const* const) ; 
 int h_exit_failure () ; 
 int h_exit_signal () ; 
 int h_exit_success () ; 
 int h_stdout_stderr (char const* const) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const* const,char*) ; 

int
main(int argc, const char *const argv[])
{
    int exitcode;

    check_args(argc, argv, 2);

    if (strcmp(argv[1], "echo") == 0) {
        check_args(argc, argv, 3);
        exitcode = h_echo(argv[2]);
    } else if (strcmp(argv[1], "exit-failure") == 0)
        exitcode = h_exit_failure();
    else if (strcmp(argv[1], "exit-signal") == 0)
        exitcode = h_exit_signal();
    else if (strcmp(argv[1], "exit-success") == 0)
        exitcode = h_exit_success();
    else if (strcmp(argv[1], "stdout-stderr") == 0) {
        check_args(argc, argv, 3);
        exitcode = h_stdout_stderr(argv[2]);
    } else {
        fprintf(stderr, "%s: Unknown helper %s\n", argv[0], argv[1]);
        exitcode = EXIT_FAILURE;
    }

    return exitcode;
}