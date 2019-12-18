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
typedef  int /*<<< orphan*/  atf_process_status_t ;
typedef  int /*<<< orphan*/  atf_list_t ;
typedef  int /*<<< orphan*/  atf_fs_path_t ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRE (int) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_process_exec_array (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void (*) ()) ; 
 scalar_t__ atf_process_stream_type (int /*<<< orphan*/  const*) ; 
 scalar_t__ atf_process_stream_type_capture ; 
 int /*<<< orphan*/  free (char const**) ; 
 int /*<<< orphan*/  list_to_array (int /*<<< orphan*/  const*,char const***) ; 

atf_error_t
atf_process_exec_list(atf_process_status_t *s,
                      const atf_fs_path_t *prog,
                      const atf_list_t *argv,
                      const atf_process_stream_t *outsb,
                      const atf_process_stream_t *errsb,
                      void (*prehook)(void))
{
    atf_error_t err;
    const char **argv2;

    PRE(outsb == NULL ||
        atf_process_stream_type(outsb) != atf_process_stream_type_capture);
    PRE(errsb == NULL ||
        atf_process_stream_type(errsb) != atf_process_stream_type_capture);

    argv2 = NULL; /* Silence GCC warning. */
    err = list_to_array(argv, &argv2);
    if (atf_is_error(err))
        goto out;

    err = atf_process_exec_array(s, prog, argv2, outsb, errsb, prehook);

    free(argv2);
out:
    return err;
}