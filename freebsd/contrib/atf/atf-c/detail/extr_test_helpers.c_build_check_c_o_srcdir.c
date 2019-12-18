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
typedef  int /*<<< orphan*/  atf_tc_t ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  atf_tc_get_config_var (int /*<<< orphan*/  const*,char*) ; 
 int build_check_c_o (int /*<<< orphan*/ ) ; 

bool
build_check_c_o_srcdir(const atf_tc_t *tc, const char *sfile)
{
    atf_fs_path_t path;

    RE(atf_fs_path_init_fmt(&path, "%s/%s",
                            atf_tc_get_config_var(tc, "srcdir"), sfile));
    const bool result = build_check_c_o(atf_fs_path_cstring(&path));
    atf_fs_path_fini(&path);
    return result;
}