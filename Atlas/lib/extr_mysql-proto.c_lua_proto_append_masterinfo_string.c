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
typedef  int /*<<< orphan*/  network_mysqld_masterinfo_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_IMPORT_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_IMPORT_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  master_connect_retry ; 
 int /*<<< orphan*/  master_host ; 
 int /*<<< orphan*/  master_lines ; 
 int /*<<< orphan*/  master_log_file ; 
 int /*<<< orphan*/  master_log_pos ; 
 int /*<<< orphan*/  master_password ; 
 int /*<<< orphan*/  master_port ; 
 int /*<<< orphan*/  master_ssl ; 
 int /*<<< orphan*/  master_ssl_ca ; 
 int /*<<< orphan*/  master_ssl_capath ; 
 int /*<<< orphan*/  master_ssl_cert ; 
 int /*<<< orphan*/  master_ssl_cipher ; 
 int /*<<< orphan*/  master_ssl_key ; 
 int /*<<< orphan*/  master_ssl_verify_server_cert ; 
 int /*<<< orphan*/  master_user ; 
 int /*<<< orphan*/  network_mysqld_masterinfo_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_masterinfo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_mysqld_masterinfo_new () ; 

__attribute__((used)) static int lua_proto_append_masterinfo_string (lua_State *L) {
        GString *packet;
        network_mysqld_masterinfo_t *info;

        luaL_checktype(L, 1, LUA_TTABLE);

        info = network_mysqld_masterinfo_new();

        LUA_IMPORT_INT(info, master_lines);
        LUA_IMPORT_STR(info, master_log_file);
        LUA_IMPORT_INT(info, master_log_pos);
        LUA_IMPORT_STR(info, master_host);
        LUA_IMPORT_STR(info, master_user);
        LUA_IMPORT_STR(info, master_password);
        LUA_IMPORT_INT(info, master_port);
        LUA_IMPORT_INT(info, master_connect_retry);
        LUA_IMPORT_INT(info, master_ssl);
        LUA_IMPORT_STR(info, master_ssl_ca);
        LUA_IMPORT_STR(info, master_ssl_capath);
        LUA_IMPORT_STR(info, master_ssl_cert);
        LUA_IMPORT_STR(info, master_ssl_cipher);
        LUA_IMPORT_STR(info, master_ssl_key);
        LUA_IMPORT_INT(info, master_ssl_verify_server_cert);

        packet = g_string_new(NULL);
        network_mysqld_masterinfo_append(packet, info);

        network_mysqld_masterinfo_free(info);

        lua_pushlstring(L, S(packet));

        g_string_free(packet, TRUE);

        return 1;
}