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
typedef  int /*<<< orphan*/  apr_strmatch_pattern ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_PTR_EQUAL (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  ABTS_PTR_NOTNULL (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 char* apr_strmatch (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_strmatch_precompile (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * p ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void test_str(abts_case *tc, void *data)
{
    apr_pool_t *pool = p;
    const apr_strmatch_pattern *pattern;
    const apr_strmatch_pattern *pattern_nocase;
    const apr_strmatch_pattern *pattern_onechar;
    const apr_strmatch_pattern *pattern_zero;
    const char *match = NULL;
    const char *input1 = "string that contains a patterN...";
    const char *input2 = "string that contains a pattern...";
    const char *input3 = "pattern at the start of a string";
    const char *input4 = "string that ends with a pattern";
    const char *input5 = "patter\200n not found, negative chars in input";
    const char *input6 = "patter\200n, negative chars, contains pattern...";

    pattern = apr_strmatch_precompile(pool, "pattern", 1);
    ABTS_PTR_NOTNULL(tc, pattern);
 
    pattern_nocase = apr_strmatch_precompile(pool, "pattern", 0);
    ABTS_PTR_NOTNULL(tc, pattern_nocase);

    pattern_onechar = apr_strmatch_precompile(pool, "g", 0);
    ABTS_PTR_NOTNULL(tc, pattern_onechar);

    pattern_zero = apr_strmatch_precompile(pool, "", 0);
    ABTS_PTR_NOTNULL(tc, pattern_zero);

    match = apr_strmatch(pattern, input1, strlen(input1));
    ABTS_PTR_EQUAL(tc, NULL, match);

    match = apr_strmatch(pattern, input2, strlen(input2));
    ABTS_PTR_EQUAL(tc, input2 + 23, match);

    match = apr_strmatch(pattern_onechar, input1, strlen(input1));
    ABTS_PTR_EQUAL(tc, input1 + 5, match);

    match = apr_strmatch(pattern_zero, input1, strlen(input1));
    ABTS_PTR_EQUAL(tc, input1, match);

    match = apr_strmatch(pattern_nocase, input1, strlen(input1));
    ABTS_PTR_EQUAL(tc, input1 + 23, match);

    match = apr_strmatch(pattern, input3, strlen(input3));
    ABTS_PTR_EQUAL(tc, input3, match);

    match = apr_strmatch(pattern, input4, strlen(input4));
    ABTS_PTR_EQUAL(tc, input4 + 24, match);

    match = apr_strmatch(pattern, input5, strlen(input5));
    ABTS_PTR_EQUAL(tc, NULL, match);

    match = apr_strmatch(pattern, input6, strlen(input6));
    ABTS_PTR_EQUAL(tc, input6 + 35, match);
}