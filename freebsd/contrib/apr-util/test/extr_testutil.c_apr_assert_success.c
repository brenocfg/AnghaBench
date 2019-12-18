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
 int /*<<< orphan*/  ABTS_FAIL (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ABTS_NOT_IMPL (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ APR_ENOTIMPL ; 
 scalar_t__ APR_SUCCESS ; 
 int STRING_MAX ; 
 char* apr_strerror (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,scalar_t__,char*) ; 

void apr_assert_success(abts_case* tc, const char* context, apr_status_t rv)
{
    if (rv == APR_ENOTIMPL) {
        ABTS_NOT_IMPL(tc, context);
    }

    if (rv != APR_SUCCESS) {
        char buf[STRING_MAX], ebuf[128];
        sprintf(buf, "%s (%d): %s\n", context, rv,
                apr_strerror(rv, ebuf, sizeof ebuf));
        ABTS_FAIL(tc, buf);
    }
}