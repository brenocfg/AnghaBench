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
typedef  int /*<<< orphan*/  atf_process_stream_t ;
typedef  int /*<<< orphan*/  atf_process_child_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_stream_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fork_with_streams (int /*<<< orphan*/ *,void (*) (void*),int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/  init_stream_w_default (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 

atf_error_t
atf_process_fork(atf_process_child_t *c,
                 void (*start)(void *),
                 const atf_process_stream_t *outsb,
                 const atf_process_stream_t *errsb,
                 void *v)
{
    atf_error_t err;
    atf_process_stream_t inherit_outsb, inherit_errsb;
    const atf_process_stream_t *real_outsb, *real_errsb;

    real_outsb = NULL;  /* Shut up GCC warning. */
    err = init_stream_w_default(outsb, &inherit_outsb, &real_outsb);
    if (atf_is_error(err))
        goto out;

    real_errsb = NULL;  /* Shut up GCC warning. */
    err = init_stream_w_default(errsb, &inherit_errsb, &real_errsb);
    if (atf_is_error(err))
        goto out_out;

    err = fork_with_streams(c, start, real_outsb, real_errsb, v);

    if (errsb == NULL)
        atf_process_stream_fini(&inherit_errsb);
out_out:
    if (outsb == NULL)
        atf_process_stream_fini(&inherit_outsb);
out:
    return err;
}