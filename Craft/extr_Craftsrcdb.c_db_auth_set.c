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
 int /*<<< orphan*/  db_auth_select (char*) ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

void db_auth_set(char *username, char *identity_token) {
    if (!db_enabled) {
        return;
    }
    static const char *query =
        "insert or replace into auth.identity_token "
        "(username, token, selected) values (?, ?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, NULL);
    sqlite3_bind_text(stmt, 2, identity_token, -1, NULL);
    sqlite3_bind_int(stmt, 3, 1);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    db_auth_select(username);
}