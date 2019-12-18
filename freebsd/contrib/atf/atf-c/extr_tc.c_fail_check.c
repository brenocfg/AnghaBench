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
struct context {scalar_t__ expect; int /*<<< orphan*/  fail_count; int /*<<< orphan*/  expect_fail_count; int /*<<< orphan*/  expect_reason; } ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;

/* Variables and functions */
 scalar_t__ EXPECT_FAIL ; 
 scalar_t__ EXPECT_PASS ; 
 char* atf_dynstr_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atf_dynstr_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_in_expect (struct context*,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
fail_check(struct context *ctx, atf_dynstr_t *reason)
{
    if (ctx->expect == EXPECT_FAIL) {
        fprintf(stderr, "*** Expected check failure: %s: %s\n",
            atf_dynstr_cstring(&ctx->expect_reason),
            atf_dynstr_cstring(reason));
        ctx->expect_fail_count++;
    } else if (ctx->expect == EXPECT_PASS) {
        fprintf(stderr, "*** Check failed: %s\n", atf_dynstr_cstring(reason));
        ctx->fail_count++;
    } else {
        error_in_expect(ctx, "Test case raised a failure but was not "
            "expecting one; reason was %s", atf_dynstr_cstring(reason));
    }

    atf_dynstr_fini(reason);
}