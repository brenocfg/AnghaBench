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
typedef  int /*<<< orphan*/  apr_dbd_transaction_t ;
typedef  int /*<<< orphan*/  apr_dbd_t ;
typedef  int /*<<< orphan*/  apr_dbd_driver_t ;

/* Variables and functions */
 char* apr_dbd_error (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int apr_dbd_query (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*,char const*) ; 
 int apr_dbd_transaction_end (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int apr_dbd_transaction_start (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  select_sequential (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int test_transactions(apr_pool_t* pool, apr_dbd_t* handle,
                             const apr_dbd_driver_t* driver)
{
    int rv = 0;
    int nrows;
    apr_dbd_transaction_t *trans = NULL;
    const char* statement;

    /* trans 1 - error out early */
    printf("Transaction 1\n");
    rv = apr_dbd_transaction_start(driver, pool, handle, &trans);
    if (rv) {
        printf("Start transaction failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    statement = "UPDATE apr_dbd_test SET col2 = 'failed'";
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    if (rv) {
        printf("Update failed: '%s'\n", apr_dbd_error(driver, handle, rv));
        apr_dbd_transaction_end(driver, pool, trans);
        return rv;
    }
    printf("%d rows updated\n", nrows);

    statement = "INSERT INTO apr_dbd_test1 (col3) values (3)";
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    if (!rv) {
        printf("Oops, invalid op succeeded but shouldn't!\n");
    }
    statement = "INSERT INTO apr_dbd_test values ('zzz', 'aaa', 3)";
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    printf("Valid insert returned %d.  Should be nonzero (fail) because transaction is bad\n", rv) ;

    rv = apr_dbd_transaction_end(driver, pool, trans);
    if (rv) {
        printf("End transaction failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    printf("Transaction ended (should be rollback) - viewing table\n"
           "A column of \"failed\" indicates transaction failed (no rollback)\n");
    select_sequential(pool, handle, driver);

    /* trans 2 - complete successfully */
    printf("Transaction 2\n");
    rv = apr_dbd_transaction_start(driver, pool, handle, &trans);
    if (rv) {
        printf("Start transaction failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    statement = "UPDATE apr_dbd_test SET col2 = 'success'";
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    if (rv) {
        printf("Update failed: '%s'\n", apr_dbd_error(driver, handle, rv));
        apr_dbd_transaction_end(driver, pool, trans);
        return rv;
    }
    printf("%d rows updated\n", nrows);
    statement = "INSERT INTO apr_dbd_test values ('aaa', 'zzz', 3)";
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    printf("Valid insert returned %d.  Should be zero (OK)\n", rv) ;
    rv = apr_dbd_transaction_end(driver, pool, trans);
    if (rv) {
        printf("End transaction failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    printf("Transaction ended (should be commit) - viewing table\n");
    select_sequential(pool, handle, driver);
    return rv;
}