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
struct context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno_test (struct context*,char const*,size_t const,int const,char const*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_requirement ; 

__attribute__((used)) static void
_atf_tc_require_errno(struct context *ctx, const char *file, const size_t line,
                      const int exp_errno, const char *expr_str,
                      const bool expr_result)
{
    errno_test(ctx, file, line, exp_errno, expr_str, expr_result,
        fail_requirement);
}