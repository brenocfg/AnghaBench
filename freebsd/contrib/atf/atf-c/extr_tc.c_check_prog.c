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
struct prog_found_pair {char const* prog; int found; } ;
struct context {int dummy; } ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNREACHABLE ; 
 char* atf_env_get (char*) ; 
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_access_x ; 
 int /*<<< orphan*/  atf_fs_eaccess (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_branch_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ atf_fs_path_is_absolute (int /*<<< orphan*/ *) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_text_for_each_word (char const*,char*,int /*<<< orphan*/ ,struct prog_found_pair*) ; 
 int /*<<< orphan*/  check_prog_in_dir ; 
 int /*<<< orphan*/  fail_requirement (struct context*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_reason_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  report_fatal_error (char*,char const*) ; 
 int /*<<< orphan*/  skip (struct context*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static atf_error_t
check_prog(struct context *ctx, const char *prog)
{
    atf_error_t err;
    atf_fs_path_t p;

    err = atf_fs_path_init_fmt(&p, "%s", prog);
    if (atf_is_error(err))
        goto out;

    if (atf_fs_path_is_absolute(&p)) {
        err = atf_fs_eaccess(&p, atf_fs_access_x);
        if (atf_is_error(err)) {
            atf_dynstr_t reason;

            atf_error_free(err);
            atf_fs_path_fini(&p);
            format_reason_fmt(&reason, NULL, 0, "The required program %s could "
                "not be found", prog);
            skip(ctx, &reason);
        }
    } else {
        const char *path = atf_env_get("PATH");
        struct prog_found_pair pf;
        atf_fs_path_t bp;

        err = atf_fs_path_branch_path(&p, &bp);
        if (atf_is_error(err))
            goto out_p;

        if (strcmp(atf_fs_path_cstring(&bp), ".") != 0) {
            atf_fs_path_fini(&bp);
            atf_fs_path_fini(&p);

            report_fatal_error("Relative paths are not allowed when searching "
                "for a program (%s)", prog);
            UNREACHABLE;
        }

        pf.prog = prog;
        pf.found = false;
        err = atf_text_for_each_word(path, ":", check_prog_in_dir, &pf);
        if (atf_is_error(err))
            goto out_bp;

        if (!pf.found) {
            atf_dynstr_t reason;

            atf_fs_path_fini(&bp);
            atf_fs_path_fini(&p);
            format_reason_fmt(&reason, NULL, 0, "The required program %s could "
                "not be found in the PATH", prog);
            fail_requirement(ctx, &reason);
        }

out_bp:
        atf_fs_path_fini(&bp);
    }

out_p:
    atf_fs_path_fini(&p);
out:
    return err;
}