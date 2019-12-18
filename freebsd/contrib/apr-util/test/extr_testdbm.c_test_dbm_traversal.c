#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dsize; int /*<<< orphan*/  dptr; } ;
struct TYPE_8__ {scalar_t__ visited; scalar_t__ deleted; TYPE_1__ key; } ;
typedef  TYPE_2__ dbm_table_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_dbm_t ;
struct TYPE_9__ {scalar_t__ dsize; int /*<<< orphan*/ * dptr; } ;
typedef  TYPE_3__ apr_datum_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_INT_EQUAL (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int APR_SUCCESS ; 
 unsigned int NUM_TABLE_ROWS ; 
 scalar_t__ apr_dbm_firstkey (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ apr_dbm_nextkey (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void test_dbm_traversal(abts_case *tc, apr_dbm_t *db, dbm_table_t *table)
{
    apr_status_t rv;
    unsigned int i;
    apr_datum_t key;

    rv = apr_dbm_firstkey(db, &key);
    ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);

    do {
        if (key.dptr == NULL || key.dsize == 0)
            break;

        for (i = 0; i < NUM_TABLE_ROWS; i++) {
            if (table[i].key.dsize != key.dsize)
                continue;
            if (memcmp(table[i].key.dptr, key.dptr, key.dsize))
                continue;
            ABTS_INT_EQUAL(tc, 0, table[i].deleted);
            ABTS_INT_EQUAL(tc, 0, table[i].visited);
            table[i].visited++;
        }

        rv = apr_dbm_nextkey(db, &key);
        ABTS_INT_EQUAL(tc, APR_SUCCESS, rv);
    } while (1);

    for (i = 0; i < NUM_TABLE_ROWS; i++) {
        if (table[i].deleted)
            continue;
        ABTS_INT_EQUAL(tc, 1, table[i].visited);
        table[i].visited = 0;
    }
}