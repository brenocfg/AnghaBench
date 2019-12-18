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
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_fs_mkstemp (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 

__attribute__((used)) static
atf_error_t
mkstemp_discard_fd(atf_fs_path_t *p)
{
    int fd;
    atf_error_t err = atf_fs_mkstemp(p, &fd);
    if (!atf_is_error(err))
        close(fd);
    return err;
}