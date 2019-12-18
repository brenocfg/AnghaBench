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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int WIFEXITED (int) ; 
 int /*<<< orphan*/  atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_utils_cat_file (int /*<<< orphan*/ ,char*) ; 
 int atf_utils_compare_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  atf_utils_copy_file (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  init_out_filename (int /*<<< orphan*/ *,int /*<<< orphan*/  const,char*,int) ; 
 size_t const strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t const) ; 
 int unlink (int /*<<< orphan*/ ) ; 
 int waitpid (int /*<<< orphan*/  const,int*,int /*<<< orphan*/ ) ; 

void
atf_utils_wait(const pid_t pid, const int exitstatus, const char *expout,
               const char *experr)
{
    int status;
    ATF_REQUIRE(waitpid(pid, &status, 0) != -1);

    atf_dynstr_t out_name;
    init_out_filename(&out_name, pid, "out", true);

    atf_dynstr_t err_name;
    init_out_filename(&err_name, pid, "err", true);

    atf_utils_cat_file(atf_dynstr_cstring(&out_name), "subprocess stdout: ");
    atf_utils_cat_file(atf_dynstr_cstring(&err_name), "subprocess stderr: ");

    ATF_REQUIRE(WIFEXITED(status));
    ATF_REQUIRE_EQ(exitstatus, WEXITSTATUS(status));

    const char *save_prefix = "save:";
    const size_t save_prefix_length = strlen(save_prefix);

    if (strlen(expout) > save_prefix_length &&
        strncmp(expout, save_prefix, save_prefix_length) == 0) {
        atf_utils_copy_file(atf_dynstr_cstring(&out_name),
                            expout + save_prefix_length);
    } else {
        ATF_REQUIRE(atf_utils_compare_file(atf_dynstr_cstring(&out_name),
                                           expout));
    }

    if (strlen(experr) > save_prefix_length &&
        strncmp(experr, save_prefix, save_prefix_length) == 0) {
        atf_utils_copy_file(atf_dynstr_cstring(&err_name),
                            experr + save_prefix_length);
    } else {
        ATF_REQUIRE(atf_utils_compare_file(atf_dynstr_cstring(&err_name),
                                           experr));
    }

    ATF_REQUIRE(unlink(atf_dynstr_cstring(&out_name)) != -1);
    ATF_REQUIRE(unlink(atf_dynstr_cstring(&err_name)) != -1);
}