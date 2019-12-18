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
struct prog_found_pair {int found; int /*<<< orphan*/  prog; } ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_access_x ; 
 int /*<<< orphan*/  atf_fs_eaccess (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_no_error () ; 

__attribute__((used)) static atf_error_t
check_prog_in_dir(const char *dir, void *data)
{
    struct prog_found_pair *pf = data;
    atf_error_t err;

    if (pf->found)
        err = atf_no_error();
    else {
        atf_fs_path_t p;

        err = atf_fs_path_init_fmt(&p, "%s/%s", dir, pf->prog);
        if (atf_is_error(err))
            goto out_p;

        err = atf_fs_eaccess(&p, atf_fs_access_x);
        if (!atf_is_error(err))
            pf->found = true;
        else {
            atf_error_free(err);
            INV(!pf->found);
            err = atf_no_error();
        }

out_p:
        atf_fs_path_fini(&p);
    }

    return err;
}