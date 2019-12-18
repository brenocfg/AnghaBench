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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  atf_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_error_format (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  atf_error_free (int /*<<< orphan*/ ) ; 
 scalar_t__ atf_is_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  child_connect (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void
do_child(void (*start)(void *),
         void *v,
         const stream_prepare_t *outsp,
         const stream_prepare_t *errsp)
{
    atf_error_t err;

    err = child_connect(outsp, STDOUT_FILENO);
    if (atf_is_error(err))
        goto out;

    err = child_connect(errsp, STDERR_FILENO);
    if (atf_is_error(err))
        goto out;

    start(v);
    UNREACHABLE;

out:
    if (atf_is_error(err)) {
        char buf[1024];

        atf_error_format(err, buf, sizeof(buf));
        fprintf(stderr, "Unhandled error: %s\n", buf);
        atf_error_free(err);

        exit(EXIT_FAILURE);
    } else
        exit(EXIT_SUCCESS);
}