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
struct exec_data {char const* const* member_0; } ;
typedef  int /*<<< orphan*/  atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_process_status_t ;
typedef  int /*<<< orphan*/  atf_process_child_t ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_child_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_fork (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct exec_data*) ; 
 int /*<<< orphan*/  atf_process_stream_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_child ; 
 int /*<<< orphan*/  init_sbs (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
atf_error_t
fork_and_wait(const char *const *argv, const atf_fs_path_t *outfile,
              const atf_fs_path_t *errfile, atf_process_status_t *status)
{
    atf_error_t err;
    atf_process_child_t child;
    atf_process_stream_t outsb, errsb;
    struct exec_data ea = { argv };

    err = init_sbs(outfile, &outsb, errfile, &errsb);
    if (atf_is_error(err))
        goto out;

    err = atf_process_fork(&child, exec_child, &outsb, &errsb, &ea);
    if (atf_is_error(err))
        goto out_sbs;

    err = atf_process_child_wait(&child, status);

out_sbs:
    atf_process_stream_fini(&errsb);
    atf_process_stream_fini(&outsb);
out:
    return err;
}