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
 int /*<<< orphan*/  atf_build_cxx_o (char const*,char const*,char const* const*,char***) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_utils_free_charpp (char**) ; 
 int /*<<< orphan*/  check_build_run (char const* const*,int*) ; 

atf_error_t
atf_check_build_cxx_o(const char *sfile,
                      const char *ofile,
                      const char *const optargs[],
                      bool *success)
{
    atf_error_t err;
    char **argv;

    err = atf_build_cxx_o(sfile, ofile, optargs, &argv);
    if (atf_is_error(err))
        goto out;

    err = check_build_run((const char *const *)argv, success);

    atf_utils_free_charpp(argv);
out:
    return err;
}