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
struct TYPE_3__ {scalar_t__ deleted; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ dbm_table_t ;
typedef  int /*<<< orphan*/  apr_dbm_t ;
typedef  int /*<<< orphan*/  abts_case ;

/* Variables and functions */
 int /*<<< orphan*/  ABTS_TRUE (int /*<<< orphan*/ *,int) ; 
 unsigned int NUM_TABLE_ROWS ; 
 int apr_dbm_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_dbm_exists(abts_case *tc, apr_dbm_t *db, dbm_table_t *table)
{
    unsigned int i;
    int cond;

    for (i = 0; i < NUM_TABLE_ROWS; i++) {
        cond = apr_dbm_exists(db, table[i].key);
        if (table[i].deleted) {
            ABTS_TRUE(tc, cond == 0);
        } else {
            ABTS_TRUE(tc, cond != 0);
        }
    }
}