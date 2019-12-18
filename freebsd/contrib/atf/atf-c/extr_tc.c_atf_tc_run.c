#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* pimpl; } ;
typedef  TYPE_2__ atf_tc_t ;
typedef  int /*<<< orphan*/  atf_error_t ;
typedef  int /*<<< orphan*/  atf_dynstr_t ;
struct TYPE_14__ {scalar_t__ fail_count; scalar_t__ expect_fail_count; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* m_body ) (TYPE_2__ const*) ;} ;

/* Variables and functions */
 TYPE_3__ Current ; 
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  atf_no_error () ; 
 int /*<<< orphan*/  context_init (TYPE_3__*,TYPE_2__ const*,char const*) ; 
 int /*<<< orphan*/  expected_failure (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_requirement (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_reason_fmt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  pass (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*) ; 
 int /*<<< orphan*/  validate_expect (TYPE_3__*) ; 

atf_error_t
atf_tc_run(const atf_tc_t *tc, const char *resfile)
{
    context_init(&Current, tc, resfile);

    tc->pimpl->m_body(tc);

    validate_expect(&Current);

    if (Current.fail_count > 0) {
        atf_dynstr_t reason;

        format_reason_fmt(&reason, NULL, 0, "%d checks failed; see output for "
            "more details", Current.fail_count);
        fail_requirement(&Current, &reason);
    } else if (Current.expect_fail_count > 0) {
        atf_dynstr_t reason;

        format_reason_fmt(&reason, NULL, 0, "%d checks failed as expected; "
            "see output for more details", Current.expect_fail_count);
        expected_failure(&Current, &reason);
    } else {
        pass(&Current);
    }
    UNREACHABLE;
    return atf_no_error();
}