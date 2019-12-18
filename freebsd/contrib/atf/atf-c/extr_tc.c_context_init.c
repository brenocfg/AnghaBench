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
struct context {char const* resfile; scalar_t__ expect_signo; scalar_t__ expect_exitcode; scalar_t__ expect_fail_count; scalar_t__ expect_previous_fail_count; int /*<<< orphan*/  expect_reason; int /*<<< orphan*/  expect; scalar_t__ fail_count; int /*<<< orphan*/  const* tc; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_PASS ; 
 int /*<<< orphan*/  atf_dynstr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_fatal_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
context_init(struct context *ctx, const atf_tc_t *tc, const char *resfile)
{
    ctx->tc = tc;
    ctx->resfile = resfile;
    ctx->fail_count = 0;
    ctx->expect = EXPECT_PASS;
    check_fatal_error(atf_dynstr_init(&ctx->expect_reason));
    ctx->expect_previous_fail_count = 0;
    ctx->expect_fail_count = 0;
    ctx->expect_exitcode = 0;
    ctx->expect_signo = 0;
}