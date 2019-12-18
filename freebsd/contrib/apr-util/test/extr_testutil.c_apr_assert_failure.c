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
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 scalar_t__ APR_ENOTIMPL ; 
 scalar_t__ APR_SUCCESS ; 
 int STRING_MAX ; 
 int /*<<< orphan*/  abts_fail (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  abts_not_impl (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,scalar_t__) ; 

void apr_assert_failure(abts_case* tc, const char* context, apr_status_t rv,
                        int lineno)
{
    if (rv == APR_ENOTIMPL) {
        abts_not_impl(tc, context, lineno);
    } else if (rv == APR_SUCCESS) {
        char buf[STRING_MAX];
        sprintf(buf, "%s (%d): expected failure, got success\n", context, rv);
        abts_fail(tc, buf, lineno);
    }
}