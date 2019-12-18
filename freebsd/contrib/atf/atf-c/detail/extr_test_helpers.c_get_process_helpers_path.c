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
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atf_tc_get_config_var (int /*<<< orphan*/  const*,char*) ; 

void
get_process_helpers_path(const atf_tc_t *tc, const bool is_detail,
                         atf_fs_path_t *path)
{
    RE(atf_fs_path_init_fmt(path, "%s/%sprocess_helpers",
                            atf_tc_get_config_var(tc, "srcdir"),
                            is_detail ? "" : "detail/"));
}