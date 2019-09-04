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
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int /*<<< orphan*/  db ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  sqlite3_bind_double (int /*<<< orphan*/ *,int,float) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

void db_save_state(float x, float y, float z, float rx, float ry) {
    if (!db_enabled) {
        return;
    }
    static const char *query =
        "insert into state (x, y, z, rx, ry) values (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_exec(db, "delete from state;", NULL, NULL, NULL);
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_double(stmt, 1, x);
    sqlite3_bind_double(stmt, 2, y);
    sqlite3_bind_double(stmt, 3, z);
    sqlite3_bind_double(stmt, 4, rx);
    sqlite3_bind_double(stmt, 5, ry);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}