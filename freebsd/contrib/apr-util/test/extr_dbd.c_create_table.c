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
typedef  int /*<<< orphan*/  apr_dbd_driver_t ;

/* Variables and functions */
 int apr_dbd_query (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*,char const*) ; 

__attribute__((used)) static int create_table(apr_pool_t* pool, apr_dbd_t* handle,
                        const apr_dbd_driver_t* driver)
{
    int rv = 0;
    int nrows;
    const char *statement = "CREATE TABLE apr_dbd_test ("
        "col1 varchar(40) not null,"
        "col2 varchar(40),"
        "col3 integer)" ;
    rv = apr_dbd_query(driver, handle, &nrows, statement);
    return rv;
}