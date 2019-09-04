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
 int /*<<< orphan*/  db ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  db_worker_stop () ; 
 int /*<<< orphan*/  delete_sign_stmt ; 
 int /*<<< orphan*/  delete_signs_stmt ; 
 int /*<<< orphan*/  get_key_stmt ; 
 int /*<<< orphan*/  insert_block_stmt ; 
 int /*<<< orphan*/  insert_light_stmt ; 
 int /*<<< orphan*/  insert_sign_stmt ; 
 int /*<<< orphan*/  load_blocks_stmt ; 
 int /*<<< orphan*/  load_lights_stmt ; 
 int /*<<< orphan*/  load_signs_stmt ; 
 int /*<<< orphan*/  set_key_stmt ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ ) ; 

void db_close() {
    if (!db_enabled) {
        return;
    }
    db_worker_stop();
    sqlite3_exec(db, "commit;", NULL, NULL, NULL);
    sqlite3_finalize(insert_block_stmt);
    sqlite3_finalize(insert_light_stmt);
    sqlite3_finalize(insert_sign_stmt);
    sqlite3_finalize(delete_sign_stmt);
    sqlite3_finalize(delete_signs_stmt);
    sqlite3_finalize(load_blocks_stmt);
    sqlite3_finalize(load_lights_stmt);
    sqlite3_finalize(load_signs_stmt);
    sqlite3_finalize(get_key_stmt);
    sqlite3_finalize(set_key_stmt);
    sqlite3_close(db);
}