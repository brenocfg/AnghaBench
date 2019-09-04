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
typedef  int /*<<< orphan*/  SignList ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  load_signs_stmt ; 
 int /*<<< orphan*/  sign_list_add (int /*<<< orphan*/ *,int,int,int,int,char const*) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ ) ; 

void db_load_signs(SignList *list, int p, int q) {
    if (!db_enabled) {
        return;
    }
    sqlite3_reset(load_signs_stmt);
    sqlite3_bind_int(load_signs_stmt, 1, p);
    sqlite3_bind_int(load_signs_stmt, 2, q);
    while (sqlite3_step(load_signs_stmt) == SQLITE_ROW) {
        int x = sqlite3_column_int(load_signs_stmt, 0);
        int y = sqlite3_column_int(load_signs_stmt, 1);
        int z = sqlite3_column_int(load_signs_stmt, 2);
        int face = sqlite3_column_int(load_signs_stmt, 3);
        const char *text = (const char *)sqlite3_column_text(
            load_signs_stmt, 4);
        sign_list_add(list, x, y, z, face, text);
    }
}