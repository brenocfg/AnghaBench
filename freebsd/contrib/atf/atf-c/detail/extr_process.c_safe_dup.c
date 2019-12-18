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

/* Variables and functions */
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  close (int const) ; 
 int dup2 (int const,int const) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static
atf_error_t
safe_dup(const int oldfd, const int newfd)
{
    atf_error_t err;

    if (oldfd != newfd) {
        if (dup2(oldfd, newfd) == -1) {
            err = atf_libc_error(errno, "Could not allocate file descriptor");
        } else {
            close(oldfd);
            err = atf_no_error();
        }
    } else
        err = atf_no_error();

    return err;
}