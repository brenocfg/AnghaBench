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

/* Variables and functions */
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  insert_sign_stmt ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ ,int,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 

void db_insert_sign(
    int p, int q, int x, int y, int z, int face, const char *text)
{
    if (!db_enabled) {
        return;
    }
    sqlite3_reset(insert_sign_stmt);
    sqlite3_bind_int(insert_sign_stmt, 1, p);
    sqlite3_bind_int(insert_sign_stmt, 2, q);
    sqlite3_bind_int(insert_sign_stmt, 3, x);
    sqlite3_bind_int(insert_sign_stmt, 4, y);
    sqlite3_bind_int(insert_sign_stmt, 5, z);
    sqlite3_bind_int(insert_sign_stmt, 6, face);
    sqlite3_bind_text(insert_sign_stmt, 7, text, -1, NULL);
    sqlite3_step(insert_sign_stmt);
}