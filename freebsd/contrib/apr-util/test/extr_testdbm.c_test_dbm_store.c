#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* deleted; int /*<<< orphan*/  val; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ dbm_table_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_dbm_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_INT_EQUAL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 void* FALSE ; 
 int NUM_TABLE_ROWS ; 
 int /*<<< orphan*/  apr_dbm_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_dbm_store(abts_case *tc, apr_dbm_t *db, dbm_table_t *table)
{
    apr_status_t rv;
    unsigned int i = NUM_TABLE_ROWS - 1;

    for (; i >= NUM_TABLE_ROWS/2; i--) {
        rv = apr_dbm_store(db, table[i].key, table[i].val);
        ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
        table[i].deleted = FALSE;
    }

    for (i = 0; i < NUM_TABLE_ROWS/2; i++) {
        rv = apr_dbm_store(db, table[i].key, table[i].val);
        ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
        table[i].deleted = FALSE;
    }
}