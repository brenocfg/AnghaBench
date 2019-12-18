#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode_changed; char* server_addr; int server_port; int create_radius; int render_radius; int delete_radius; int /*<<< orphan*/  block1; int /*<<< orphan*/  block0; int /*<<< orphan*/  db_path; void* mode; } ;

/* Variables and functions */
 char* DB_PATH ; 
 int DEFAULT_PORT ; 
 int MAX_ADDR_LENGTH ; 
 int MAX_PATH_LENGTH ; 
 void* MODE_OFFLINE ; 
 void* MODE_ONLINE ; 
 int /*<<< orphan*/  add_message (char*) ; 
 int /*<<< orphan*/  array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  client_talk (char const*) ; 
 int /*<<< orphan*/  copy () ; 
 int /*<<< orphan*/  cube (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cylinder (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ db_auth_select (char*) ; 
 int /*<<< orphan*/  db_auth_select_none () ; 
 int /*<<< orphan*/  db_auth_set (char*,char*) ; 
 TYPE_1__* g ; 
 int /*<<< orphan*/  login () ; 
 int /*<<< orphan*/  paste () ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,...) ; 
 int /*<<< orphan*/  sphere (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int sscanf (char const*,char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  tree (int /*<<< orphan*/ *) ; 

void parse_command(const char *buffer, int forward) {
    char username[128] = {0};
    char token[128] = {0};
    char server_addr[MAX_ADDR_LENGTH];
    int server_port = DEFAULT_PORT;
    char filename[MAX_PATH_LENGTH];
    int radius, count, xc, yc, zc;
    if (sscanf(buffer, "/identity %128s %128s", username, token) == 2) {
        db_auth_set(username, token);
        add_message("Successfully imported identity token!");
        login();
    }
    else if (strcmp(buffer, "/logout") == 0) {
        db_auth_select_none();
        login();
    }
    else if (sscanf(buffer, "/login %128s", username) == 1) {
        if (db_auth_select(username)) {
            login();
        }
        else {
            add_message("Unknown username.");
        }
    }
    else if (sscanf(buffer,
        "/online %128s %d", server_addr, &server_port) >= 1)
    {
        g->mode_changed = 1;
        g->mode = MODE_ONLINE;
        strncpy(g->server_addr, server_addr, MAX_ADDR_LENGTH);
        g->server_port = server_port;
        snprintf(g->db_path, MAX_PATH_LENGTH,
            "cache.%s.%d.db", g->server_addr, g->server_port);
    }
    else if (sscanf(buffer, "/offline %128s", filename) == 1) {
        g->mode_changed = 1;
        g->mode = MODE_OFFLINE;
        snprintf(g->db_path, MAX_PATH_LENGTH, "%s.db", filename);
    }
    else if (strcmp(buffer, "/offline") == 0) {
        g->mode_changed = 1;
        g->mode = MODE_OFFLINE;
        snprintf(g->db_path, MAX_PATH_LENGTH, "%s", DB_PATH);
    }
    else if (sscanf(buffer, "/view %d", &radius) == 1) {
        if (radius >= 1 && radius <= 24) {
            g->create_radius = radius;
            g->render_radius = radius;
            g->delete_radius = radius + 4;
        }
        else {
            add_message("Viewing distance must be between 1 and 24.");
        }
    }
    else if (strcmp(buffer, "/copy") == 0) {
        copy();
    }
    else if (strcmp(buffer, "/paste") == 0) {
        paste();
    }
    else if (strcmp(buffer, "/tree") == 0) {
        tree(&g->block0);
    }
    else if (sscanf(buffer, "/array %d %d %d", &xc, &yc, &zc) == 3) {
        array(&g->block1, &g->block0, xc, yc, zc);
    }
    else if (sscanf(buffer, "/array %d", &count) == 1) {
        array(&g->block1, &g->block0, count, count, count);
    }
    else if (strcmp(buffer, "/fcube") == 0) {
        cube(&g->block0, &g->block1, 1);
    }
    else if (strcmp(buffer, "/cube") == 0) {
        cube(&g->block0, &g->block1, 0);
    }
    else if (sscanf(buffer, "/fsphere %d", &radius) == 1) {
        sphere(&g->block0, radius, 1, 0, 0, 0);
    }
    else if (sscanf(buffer, "/sphere %d", &radius) == 1) {
        sphere(&g->block0, radius, 0, 0, 0, 0);
    }
    else if (sscanf(buffer, "/fcirclex %d", &radius) == 1) {
        sphere(&g->block0, radius, 1, 1, 0, 0);
    }
    else if (sscanf(buffer, "/circlex %d", &radius) == 1) {
        sphere(&g->block0, radius, 0, 1, 0, 0);
    }
    else if (sscanf(buffer, "/fcircley %d", &radius) == 1) {
        sphere(&g->block0, radius, 1, 0, 1, 0);
    }
    else if (sscanf(buffer, "/circley %d", &radius) == 1) {
        sphere(&g->block0, radius, 0, 0, 1, 0);
    }
    else if (sscanf(buffer, "/fcirclez %d", &radius) == 1) {
        sphere(&g->block0, radius, 1, 0, 0, 1);
    }
    else if (sscanf(buffer, "/circlez %d", &radius) == 1) {
        sphere(&g->block0, radius, 0, 0, 0, 1);
    }
    else if (sscanf(buffer, "/fcylinder %d", &radius) == 1) {
        cylinder(&g->block0, &g->block1, radius, 1);
    }
    else if (sscanf(buffer, "/cylinder %d", &radius) == 1) {
        cylinder(&g->block0, &g->block1, radius, 0);
    }
    else if (forward) {
        client_talk(buffer);
    }
}