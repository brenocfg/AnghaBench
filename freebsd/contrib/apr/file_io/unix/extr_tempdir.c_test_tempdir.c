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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_file_close (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_mktemp (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_file_putc (char,int /*<<< orphan*/ *) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_tempdir(const char *temp_dir, apr_pool_t *p)
{
    apr_file_t *dummy_file;
    char *path = apr_pstrcat(p, temp_dir, "/apr-tmp.XXXXXX", NULL);

    if (apr_file_mktemp(&dummy_file, path, 0, p) == APR_SUCCESS) {
        if (apr_file_putc('!', dummy_file) == APR_SUCCESS) {
            if (apr_file_close(dummy_file) == APR_SUCCESS) {
                return 1;
            }
        }
    }
    return 0;
}