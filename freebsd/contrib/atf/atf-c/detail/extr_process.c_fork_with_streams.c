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
typedef  int /*<<< orphan*/  stream_prepare_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_process_child_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_libc_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  do_child (void (*) (void*),void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_parent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int fork () ; 
 int /*<<< orphan*/  stream_prepare_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_prepare_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static
atf_error_t
fork_with_streams(atf_process_child_t *c,
                  void (*start)(void *),
                  const atf_process_stream_t *outsb,
                  const atf_process_stream_t *errsb,
                  void *v)
{
    atf_error_t err;
    stream_prepare_t outsp;
    stream_prepare_t errsp;
    pid_t pid;

    err = stream_prepare_init(&outsp, outsb);
    if (atf_is_error(err))
        goto out;

    err = stream_prepare_init(&errsp, errsb);
    if (atf_is_error(err))
        goto err_outpipe;

    pid = fork();
    if (pid == -1) {
        err = atf_libc_error(errno, "Failed to fork");
        goto err_errpipe;
    }

    if (pid == 0) {
        do_child(start, v, &outsp, &errsp);
        UNREACHABLE;
        abort();
        err = atf_no_error();
    } else {
        err = do_parent(c, pid, &outsp, &errsp);
        if (atf_is_error(err))
            goto err_errpipe;
    }

    goto out;

err_errpipe:
    stream_prepare_fini(&errsp);
err_outpipe:
    stream_prepare_fini(&outsp);

out:
    return err;
}