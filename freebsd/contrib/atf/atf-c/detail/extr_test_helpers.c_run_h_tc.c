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
struct run_h_tc_data {char const* member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;
typedef  int /*<<< orphan*/  atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_process_status_t ;
typedef  int /*<<< orphan*/  atf_process_child_t ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_fs_path_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_fs_path_init_fmt (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  atf_process_child_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_fork (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct run_h_tc_data*) ; 
 int /*<<< orphan*/  atf_process_status_exited (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_status_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_stream_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_stream_init_redirect_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  run_h_tc_child ; 

void
run_h_tc(atf_tc_t *tc, const char *outname, const char *errname,
         const char *resname)
{
    atf_fs_path_t outpath, errpath;
    atf_process_stream_t outb, errb;
    atf_process_child_t child;
    atf_process_status_t status;

    RE(atf_fs_path_init_fmt(&outpath, outname));
    RE(atf_fs_path_init_fmt(&errpath, errname));

    struct run_h_tc_data data = { tc, resname };

    RE(atf_process_stream_init_redirect_path(&outb, &outpath));
    RE(atf_process_stream_init_redirect_path(&errb, &errpath));
    RE(atf_process_fork(&child, run_h_tc_child, &outb, &errb, &data));
    atf_process_stream_fini(&errb);
    atf_process_stream_fini(&outb);

    RE(atf_process_child_wait(&child, &status));
    ATF_CHECK(atf_process_status_exited(&status));
    atf_process_status_fini(&status);

    atf_fs_path_fini(&errpath);
    atf_fs_path_fini(&outpath);
}