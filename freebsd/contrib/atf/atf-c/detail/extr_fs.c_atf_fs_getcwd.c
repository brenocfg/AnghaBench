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
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

atf_error_t
atf_fs_getcwd(atf_fs_path_t *p)
{
    atf_error_t err;
    char *cwd;

#if defined(HAVE_GETCWD_DYN)
    cwd = getcwd(NULL, 0);
#else
    cwd = getcwd(NULL, MAXPATHLEN);
#endif
    if (cwd == NULL) {
        err = atf_libc_error(errno, "Cannot determine current directory");
        goto out;
    }

    err = atf_fs_path_init_fmt(p, "%s", cwd);
    free(cwd);

out:
    return err;
}