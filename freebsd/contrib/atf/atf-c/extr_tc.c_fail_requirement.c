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
struct context {scalar_t__ expect; int /*<<< orphan*/  resfile; } ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ EXPECT_FAIL ; 
 scalar_t__ EXPECT_PASS ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_resfile (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_in_expect (struct context*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_failure (struct context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fail_requirement(struct context *ctx, atf_dynstr_t *reason)
{
    if (ctx->expect == EXPECT_FAIL) {
        expected_failure(ctx, reason);
    } else if (ctx->expect == EXPECT_PASS) {
        create_resfile(ctx->resfile, "failed", -1, reason);
        exit(EXIT_FAILURE);
    } else {
        error_in_expect(ctx, "Test case raised a failure but was not "
            "expecting one; reason was %s", atf_dynstr_cstring(reason));
    }
    UNREACHABLE;
}