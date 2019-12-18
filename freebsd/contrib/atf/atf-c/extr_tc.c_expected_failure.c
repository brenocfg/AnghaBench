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
struct context {int /*<<< orphan*/  resfile; int /*<<< orphan*/  expect_reason; } ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_prepend_fmt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fatal_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_resfile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expected_failure(struct context *ctx, atf_dynstr_t *reason)
{
    check_fatal_error(atf_dynstr_prepend_fmt(reason, "%s: ",
        atf_dynstr_cstring(&ctx->expect_reason)));
    create_resfile(ctx->resfile, "expected_failure", -1, reason);
    exit(EXIT_SUCCESS);
}