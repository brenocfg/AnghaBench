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
typedef  int /*<<< orphan*/  apr_file_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_ASSERT (int /*<<< orphan*/ *,char*,int) ; 
 int APR_FOPEN_CREATE ; 
 int APR_FOPEN_READ ; 
 int APR_FOPEN_TRUNCATE ; 
 int APR_FOPEN_WRITE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_file_open (int /*<<< orphan*/ **,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ apr_file_puts (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static apr_file_t *make_test_file(abts_case *tc, const char *fname,
                                  const char *contents)
{
    apr_file_t *f;

    ABTS_ASSERT(tc, "create test file",
                apr_file_open(&f, fname,
                              APR_FOPEN_READ|APR_FOPEN_WRITE|APR_FOPEN_TRUNCATE|APR_FOPEN_CREATE,
                              APR_OS_DEFAULT, p) == APR_SUCCESS);
    
    ABTS_ASSERT(tc, "write test file contents",
                apr_file_puts(contents, f) == APR_SUCCESS);

    return f;
}