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
typedef  int /*<<< orphan*/  apr_dbd_t ;
typedef  int /*<<< orphan*/  apr_dbd_row_t ;
typedef  int /*<<< orphan*/  apr_dbd_results_t ;
typedef  int /*<<< orphan*/  apr_dbd_prepared_t ;
typedef  int /*<<< orphan*/  apr_dbd_driver_t ;

/* Variables and functions */
 char* apr_dbd_error (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 char* apr_dbd_get_entry (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int apr_dbd_get_row (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int apr_dbd_num_cols (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int apr_dbd_prepare (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ **) ; 
 int apr_dbd_pvselect (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int test_pselect(apr_pool_t* pool, apr_dbd_t* handle,
                        const apr_dbd_driver_t* driver)
{
    int rv = 0;
    int i, n;
    const char *query =
        "SELECT * FROM apr_dbd_test WHERE col3 <= %s or col1 = 'bar'" ;
    const char *label = "lowvalues";
    apr_dbd_prepared_t *statement = NULL;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;
    const char *entry = NULL;

    rv = apr_dbd_prepare(driver, pool, handle, query, label, &statement);
    if (rv) {
        printf("Prepare statement failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    rv = apr_dbd_pvselect(driver, pool, handle, &res, statement, 0, "3", NULL);
    if (rv) {
        printf("Exec of prepared statement failed!\n%s\n",
               apr_dbd_error(driver, handle, rv));
        return rv;
    }
    i = 0;
    printf("Selecting rows where col3 <= 3 and bar row where it's unset.\nShould show four rows.\n");
    for (rv = apr_dbd_get_row(driver, pool, res, &row, -1);
         rv == 0;
         rv = apr_dbd_get_row(driver, pool, res, &row, -1)) {
        printf("ROW %d:	", ++i) ;
        for (n = 0; n < apr_dbd_num_cols(driver, res); ++n) {
            entry = apr_dbd_get_entry(driver, row, n);
            if (entry == NULL) {
                printf("(null)	") ;
            }
            else {
                printf("%s	", entry);
            }
        }
	fputs("\n", stdout);
    }
    return (rv == -1) ? 0 : 1;
}