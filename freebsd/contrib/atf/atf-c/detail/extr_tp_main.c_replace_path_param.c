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
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  atf_is_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
atf_error_t
replace_path_param(atf_fs_path_t *param, const char *value)
{
    atf_error_t err;
    atf_fs_path_t temp;

    err = atf_fs_path_init_fmt(&temp, "%s", value);
    if (!atf_is_error(err)) {
        atf_fs_path_fini(param);
        *param = temp;
    }

    return err;
}