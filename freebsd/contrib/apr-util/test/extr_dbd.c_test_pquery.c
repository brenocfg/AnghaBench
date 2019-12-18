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
typedef  int /*<<< orphan*/  apr_dbd_prepared_t ;
typedef  int /*<<< orphan*/  apr_dbd_driver_t ;

/* Variables and functions */
 char* apr_dbd_error (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int apr_dbd_prepare (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ **) ; 
 int apr_dbd_pvquery (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_dbd_transaction_end (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_dbd_transaction_start (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  select_sequential (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int test_pquery(apr_pool_t* pool, apr_dbd_t* handle,
                       const apr_dbd_driver_t* driver)
{
    int rv = 0;
    const char *query = "INSERT INTO apr_dbd_test VALUES (%s, %s, %d)";
    apr_dbd_prepared_t *statement = NULL;
    const char *label = "testpquery";
    int nrows;
    apr_dbd_transaction_t *trans =0;

    rv = apr_dbd_prepare(driver, pool, handle, query, label, &statement);
    /* rv = apr_dbd_prepare(driver, pool, handle, query, NULL, &statement); */
    if (rv) {
        printf("Prepare statement failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    apr_dbd_transaction_start(driver, pool, handle, &trans);
    rv = apr_dbd_pvquery(driver, pool, handle, &nrows, statement,
                         "prepared", "insert", "2", NULL);
    apr_dbd_transaction_end(driver, pool, trans);
    if (rv) {
        printf("Exec of prepared statement failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    printf("Showing table (should now contain row \"prepared insert 2\")\n");
    select_sequential(pool, handle, driver);
    return rv;
}