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
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_bucket_brigade ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ABTS_STR_NEQUAL (int /*<<< orphan*/ *,char const*,char*,scalar_t__) ; 
 int /*<<< orphan*/  apr_assert_success (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_brigade_flatten (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void flatten_match(abts_case *tc, const char *ctx,
                          apr_bucket_brigade *bb,
                          const char *expect)
{
    apr_size_t elen = strlen(expect);
    char *buf = malloc(elen);
    apr_size_t len = elen;
    char msg[200];

    sprintf(msg, "%s: flatten brigade", ctx);
    apr_assert_success(tc, msg, apr_brigade_flatten(bb, buf, &len));
    sprintf(msg, "%s: length match (%ld not %ld)", ctx,
            (long)len, (long)elen);
    ABTS_ASSERT(tc, msg, len == elen);
    sprintf(msg, "%s: result match", msg);
    ABTS_STR_NEQUAL(tc, expect, buf, len);
    free(buf);
}