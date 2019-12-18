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
struct params {int /*<<< orphan*/  m_config; int /*<<< orphan*/  m_srcdir; } ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  atf_dynstr_fini (int /*<<< orphan*/ *) ; 
 int atf_equal_dynstr_cstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  atf_fs_exists (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  atf_fs_path_append_fmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_is_absolute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_leaf_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_to_absolute (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_map_insert (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  srcdir_strip_libtool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_error (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
atf_error_t
handle_srcdir(struct params *p)
{
    atf_error_t err;
    atf_dynstr_t leafname;
    atf_fs_path_t exe, srcdir;
    bool b;

    err = atf_fs_path_copy(&srcdir, &p->m_srcdir);
    if (atf_is_error(err))
        goto out;

    if (!atf_fs_path_is_absolute(&srcdir)) {
        atf_fs_path_t srcdirabs;

        err = atf_fs_path_to_absolute(&srcdir, &srcdirabs);
        if (atf_is_error(err))
            goto out_srcdir;

        atf_fs_path_fini(&srcdir);
        srcdir = srcdirabs;
    }

    err = atf_fs_path_leaf_name(&srcdir, &leafname);
    if (atf_is_error(err))
        goto out_srcdir;
    else {
        const bool libs = atf_equal_dynstr_cstring(&leafname, ".libs");
        atf_dynstr_fini(&leafname);

        if (libs) {
            err = srcdir_strip_libtool(&srcdir);
            if (atf_is_error(err))
                goto out;
        }
    }

    err = atf_fs_path_copy(&exe, &srcdir);
    if (atf_is_error(err))
        goto out_srcdir;

    err = atf_fs_path_append_fmt(&exe, "%s", progname);
    if (atf_is_error(err))
        goto out_exe;

    err = atf_fs_exists(&exe, &b);
    if (!atf_is_error(err)) {
        if (b) {
            err = atf_map_insert(&p->m_config, "srcdir",
                                 strdup(atf_fs_path_cstring(&srcdir)), true);
        } else {
            err = user_error("Cannot find the test program in the source "
                             "directory `%s'", atf_fs_path_cstring(&srcdir));
        }
    }

out_exe:
    atf_fs_path_fini(&exe);
out_srcdir:
    atf_fs_path_fini(&srcdir);
out:
    return err;
}