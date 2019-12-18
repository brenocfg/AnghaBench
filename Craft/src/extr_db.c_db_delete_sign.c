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
 int /*<<< orphan*/  delete_sign_stmt ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ ) ; 

void db_delete_sign(int x, int y, int z, int face) {
    if (!db_enabled) {
        return;
    }
    sqlite3_reset(delete_sign_stmt);
    sqlite3_bind_int(delete_sign_stmt, 1, x);
    sqlite3_bind_int(delete_sign_stmt, 2, y);
    sqlite3_bind_int(delete_sign_stmt, 3, z);
    sqlite3_bind_int(delete_sign_stmt, 4, face);
    sqlite3_step(delete_sign_stmt);
}