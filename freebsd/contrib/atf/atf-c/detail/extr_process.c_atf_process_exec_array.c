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
struct exec_args {char const* const* member_1; void (* member_2 ) () ;int /*<<< orphan*/  const* member_0; } ;
typedef  int /*<<< orphan*/  atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_process_status_t ;
typedef  int /*<<< orphan*/  atf_process_child_t ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  INV (int) ; 
 int /*<<< orphan*/  PRE (int) ; 
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_error_is (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_libc_error_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_child_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_process_fork (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,struct exec_args*) ; 
 scalar_t__ atf_process_stream_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ atf_process_stream_type_capture ; 
 int /*<<< orphan*/  do_exec ; 

atf_error_t
atf_process_exec_array(atf_process_status_t *s,
                       const atf_fs_path_t *prog,
                       const char *const *argv,
                       const atf_process_stream_t *outsb,
                       const atf_process_stream_t *errsb,
                       void (*prehook)(void))
{
    atf_error_t err;
    atf_process_child_t c;
    struct exec_args ea = { prog, argv, prehook };

    PRE(outsb == NULL ||
        atf_process_stream_type(outsb) != atf_process_stream_type_capture);
    PRE(errsb == NULL ||
        atf_process_stream_type(errsb) != atf_process_stream_type_capture);

    err = atf_process_fork(&c, do_exec, outsb, errsb, &ea);
    if (atf_is_error(err))
        goto out;

again:
    err = atf_process_child_wait(&c, s);
    if (atf_is_error(err)) {
        INV(atf_error_is(err, "libc") && atf_libc_error_code(err) == EINTR);
        atf_error_free(err);
        goto again;
    }

out:
    return err;
}