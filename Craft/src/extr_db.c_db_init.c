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
 int /*<<< orphan*/  db_worker_start () ; 
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
 int sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int db_init(char *path) {
    if (!db_enabled) {
        return 0;
    }
    static const char *create_query =
        "attach database 'auth.db' as auth;"
        "create table if not exists auth.identity_token ("
        "   username text not null,"
        "   token text not null,"
        "   selected int not null"
        ");"
        "create unique index if not exists auth.identity_token_username_idx"
        "   on identity_token (username);"
        "create table if not exists state ("
        "   x float not null,"
        "   y float not null,"
        "   z float not null,"
        "   rx float not null,"
        "   ry float not null"
        ");"
        "create table if not exists block ("
        "    p int not null,"
        "    q int not null,"
        "    x int not null,"
        "    y int not null,"
        "    z int not null,"
        "    w int not null"
        ");"
        "create table if not exists light ("
        "    p int not null,"
        "    q int not null,"
        "    x int not null,"
        "    y int not null,"
        "    z int not null,"
        "    w int not null"
        ");"
        "create table if not exists key ("
        "    p int not null,"
        "    q int not null,"
        "    key int not null"
        ");"
        "create table if not exists sign ("
        "    p int not null,"
        "    q int not null,"
        "    x int not null,"
        "    y int not null,"
        "    z int not null,"
        "    face int not null,"
        "    text text not null"
        ");"
        "create unique index if not exists block_pqxyz_idx on block (p, q, x, y, z);"
        "create unique index if not exists light_pqxyz_idx on light (p, q, x, y, z);"
        "create unique index if not exists key_pq_idx on key (p, q);"
        "create unique index if not exists sign_xyzface_idx on sign (x, y, z, face);"
        "create index if not exists sign_pq_idx on sign (p, q);";
    static const char *insert_block_query =
        "insert or replace into block (p, q, x, y, z, w) "
        "values (?, ?, ?, ?, ?, ?);";
    static const char *insert_light_query =
        "insert or replace into light (p, q, x, y, z, w) "
        "values (?, ?, ?, ?, ?, ?);";
    static const char *insert_sign_query =
        "insert or replace into sign (p, q, x, y, z, face, text) "
        "values (?, ?, ?, ?, ?, ?, ?);";
    static const char *delete_sign_query =
        "delete from sign where x = ? and y = ? and z = ? and face = ?;";
    static const char *delete_signs_query =
        "delete from sign where x = ? and y = ? and z = ?;";
    static const char *load_blocks_query =
        "select x, y, z, w from block where p = ? and q = ?;";
    static const char *load_lights_query =
        "select x, y, z, w from light where p = ? and q = ?;";
    static const char *load_signs_query =
        "select x, y, z, face, text from sign where p = ? and q = ?;";
    static const char *get_key_query =
        "select key from key where p = ? and q = ?;";
    static const char *set_key_query =
        "insert or replace into key (p, q, key) "
        "values (?, ?, ?);";
    int rc;
    rc = sqlite3_open(path, &db);
    if (rc) return rc;
    rc = sqlite3_exec(db, create_query, NULL, NULL, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(
        db, insert_block_query, -1, &insert_block_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(
        db, insert_light_query, -1, &insert_light_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(
        db, insert_sign_query, -1, &insert_sign_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(
        db, delete_sign_query, -1, &delete_sign_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(
        db, delete_signs_query, -1, &delete_signs_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(db, load_blocks_query, -1, &load_blocks_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(db, load_lights_query, -1, &load_lights_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(db, load_signs_query, -1, &load_signs_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(db, get_key_query, -1, &get_key_stmt, NULL);
    if (rc) return rc;
    rc = sqlite3_prepare_v2(db, set_key_query, -1, &set_key_stmt, NULL);
    if (rc) return rc;
    sqlite3_exec(db, "begin;", NULL, NULL, NULL);
    db_worker_start();
    return 0;
}