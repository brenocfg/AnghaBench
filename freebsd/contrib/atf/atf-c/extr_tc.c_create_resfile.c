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
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int const STDERR_FILENO ; 
 int const STDOUT_FILENO ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  atf_dynstr_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  check_fatal_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int const) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  write_resfile (int const,char const*,int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
create_resfile(const char *resfile, const char *result, const int arg,
               atf_dynstr_t *reason)
{
    atf_error_t err;

    if (strcmp("/dev/stdout", resfile) == 0) {
        err = write_resfile(STDOUT_FILENO, result, arg, reason);
    } else if (strcmp("/dev/stderr", resfile) == 0) {
        err = write_resfile(STDERR_FILENO, result, arg, reason);
    } else {
        const int fd = open(resfile, O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1) {
            err = atf_libc_error(errno, "Cannot create results file '%s'",
                                 resfile);
        } else {
            err = write_resfile(fd, result, arg, reason);
            close(fd);
        }
    }

    if (reason != NULL)
        atf_dynstr_fini(reason);

    check_fatal_error(err);
}