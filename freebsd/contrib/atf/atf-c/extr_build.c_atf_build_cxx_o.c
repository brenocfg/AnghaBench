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
typedef  int /*<<< orphan*/  atf_list_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_BUILD_CPPFLAGS ; 
 int /*<<< orphan*/  ATF_BUILD_CXX ; 
 int /*<<< orphan*/  ATF_BUILD_CXXFLAGS ; 
 int /*<<< orphan*/  append_config_var (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_optargs (char const* const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_src_out (char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_list_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_to_array (int /*<<< orphan*/ *,char***) ; 

atf_error_t
atf_build_cxx_o(const char *sfile,
                const char *ofile,
                const char *const optargs[],
                char ***argv)
{
    atf_error_t err;
    atf_list_t argv_list;

    err = atf_list_init(&argv_list);
    if (atf_is_error(err))
        goto out;

    err = append_config_var("ATF_BUILD_CXX", ATF_BUILD_CXX, &argv_list);
    if (atf_is_error(err))
        goto out_list;

    err = append_config_var("ATF_BUILD_CPPFLAGS", ATF_BUILD_CPPFLAGS,
                            &argv_list);
    if (atf_is_error(err))
        goto out_list;

    err = append_config_var("ATF_BUILD_CXXFLAGS", ATF_BUILD_CXXFLAGS,
                            &argv_list);
    if (atf_is_error(err))
        goto out_list;

    if (optargs != NULL) {
        err = append_optargs(optargs, &argv_list);
        if (atf_is_error(err))
            goto out_list;
    }

    err = append_src_out(sfile, ofile, &argv_list);
    if (atf_is_error(err))
        goto out_list;

    err = list_to_array(&argv_list, argv);
    if (atf_is_error(err))
        goto out_list;

out_list:
    atf_list_fini(&argv_list);
out:
    return err;
}