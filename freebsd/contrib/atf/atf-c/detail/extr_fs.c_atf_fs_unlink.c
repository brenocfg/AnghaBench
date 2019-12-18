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
 char* atf_fs_path_cstring (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ unlink (char const*) ; 

atf_error_t
atf_fs_unlink(const atf_fs_path_t *p)
{
    atf_error_t err;
    const char *path;

    path = atf_fs_path_cstring(p);

    if (unlink(path) != 0)
        err = atf_libc_error(errno, "Cannot unlink file: '%s'", path);
    else
        err = atf_no_error();

    return err;
}