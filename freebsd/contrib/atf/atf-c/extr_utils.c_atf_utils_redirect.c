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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int const STDERR_FILENO ; 
 int const STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int const) ; 
 int dup2 (int const,int const) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void
atf_utils_redirect(const int target_fd, const char *name)
{
    if (target_fd == STDOUT_FILENO)
        fflush(stdout);
    else if (target_fd == STDERR_FILENO)
        fflush(stderr);

    const int new_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (new_fd == -1)
        err(EXIT_FAILURE, "Cannot create %s", name);
    if (new_fd != target_fd) {
        if (dup2(new_fd, target_fd) == -1)
            err(EXIT_FAILURE, "Cannot redirect to fd %d", target_fd);
    }
    close(new_fd);
}