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
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_INCLUDEDIR ; 
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_check_build_c_o (char const*,char*,char const**,int*) ; 
 char* atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_init_fmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_env_get_with_default (char*,int /*<<< orphan*/ ) ; 

bool
build_check_c_o(const char *path)
{
    bool success;
    atf_dynstr_t iflag;
    const char *optargs[4];

    RE(atf_dynstr_init_fmt(&iflag, "-I%s", atf_env_get_with_default(
        "ATF_INCLUDEDIR", ATF_INCLUDEDIR)));

    optargs[0] = atf_dynstr_cstring(&iflag);
    optargs[1] = "-Wall";
    optargs[2] = "-Werror";
    optargs[3] = NULL;

    RE(atf_check_build_c_o(path, "test.o", optargs, &success));

    atf_dynstr_fini(&iflag);

    return success;
}