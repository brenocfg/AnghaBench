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
typedef  int /*<<< orphan*/  dbm_table_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_dbm_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_INT_EQUAL (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  APR_DBM_READONLY ; 
 int /*<<< orphan*/  APR_DBM_RWCREATE ; 
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  apr_dbm_close (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_dbm_open_ex (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_pstrcat (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * generate_table () ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  test_dbm_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_dbm_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_dbm_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_dbm_store (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_dbm_traversal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_dbm(abts_case *tc, void *data)
{
    apr_dbm_t *db;
    apr_status_t rv;
    dbm_table_t *table;
    const char *type = data;
    const char *file = apr_pstrcat(p, "data/test-", type, NULL);

    rv = apr_dbm_open_ex(&db, type, file, APR_DBM_RWCREATE, APR_OS_DEFAULT, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    if (rv != APR_SUCCESS)
        return;

    table = generate_table();

    test_dbm_store(tc, db, table);
    test_dbm_fetch(tc, db, table);
    test_dbm_delete(tc, db, table);
    test_dbm_exists(tc, db, table);
    test_dbm_traversal(tc, db, table);

    apr_dbm_close(db);

    rv = apr_dbm_open_ex(&db, type, file, APR_DBM_READONLY, APR_OS_DEFAULT, p);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    if (rv != APR_SUCCESS)
        return;

    test_dbm_exists(tc, db, table);
    test_dbm_traversal(tc, db, table);
    test_dbm_fetch(tc, db, table);

    apr_dbm_close(db);
}