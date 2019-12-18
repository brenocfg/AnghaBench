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
struct context {int /*<<< orphan*/  expect; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT_PASS ; 
 int /*<<< orphan*/  validate_expect (struct context*) ; 

__attribute__((used)) static void
_atf_tc_expect_pass(struct context *ctx)
{
    validate_expect(ctx);

    ctx->expect = EXPECT_PASS;
}