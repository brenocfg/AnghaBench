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
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  db_enabled ; 
 int /*<<< orphan*/  load_lights_stmt ; 
 int /*<<< orphan*/  load_mtx ; 
 int /*<<< orphan*/  map_set (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ ,int,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ ) ; 

void db_load_lights(Map *map, int p, int q) {
    if (!db_enabled) {
        return;
    }
    mtx_lock(&load_mtx);
    sqlite3_reset(load_lights_stmt);
    sqlite3_bind_int(load_lights_stmt, 1, p);
    sqlite3_bind_int(load_lights_stmt, 2, q);
    while (sqlite3_step(load_lights_stmt) == SQLITE_ROW) {
        int x = sqlite3_column_int(load_lights_stmt, 0);
        int y = sqlite3_column_int(load_lights_stmt, 1);
        int z = sqlite3_column_int(load_lights_stmt, 2);
        int w = sqlite3_column_int(load_lights_stmt, 3);
        map_set(map, x, y, z, w);
    }
    mtx_unlock(&load_mtx);
}