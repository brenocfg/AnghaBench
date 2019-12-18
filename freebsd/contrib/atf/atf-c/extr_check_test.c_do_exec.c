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
typedef  int /*<<< orphan*/  atf_check_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_check_exec_array (char const**,int /*<<< orphan*/ *) ; 
 char* atf_fs_path_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_process_helpers_path (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 

__attribute__((used)) static
void
do_exec(const atf_tc_t *tc, const char *helper_name, atf_check_result_t *r)
{
    atf_fs_path_t process_helpers;
    const char *argv[3];

    get_process_helpers_path(tc, false, &process_helpers);

    argv[0] = atf_fs_path_cstring(&process_helpers);
    argv[1] = helper_name;
    argv[2] = NULL;
    printf("Executing %s %s\n", argv[0], argv[1]);
    RE(atf_check_exec_array(argv, r));

    atf_fs_path_fini(&process_helpers);
}