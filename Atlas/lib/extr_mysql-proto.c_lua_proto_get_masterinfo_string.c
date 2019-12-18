#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ offset; TYPE_3__* data; } ;
typedef  TYPE_1__ network_packet ;
struct TYPE_11__ {int master_lines; } ;
typedef  TYPE_2__ network_mysqld_masterinfo_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_12__ {char* str; size_t len; } ;
typedef  TYPE_3__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  LUA_EXPORT_INT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_EXPORT_STR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  network_mysqld_masterinfo_free (TYPE_2__*) ; 
 scalar_t__ network_mysqld_masterinfo_get (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* network_mysqld_masterinfo_new () ; 

__attribute__((used)) static int lua_proto_get_masterinfo_string (lua_State *L) {
	size_t packet_len;
	const char *packet_str = luaL_checklstring(L, 1, &packet_len);
	network_mysqld_masterinfo_t *info;

	network_packet packet;
	GString s;
	int err = 0;

	s.str = (char *)packet_str;
	s.len = packet_len;

	packet.data = &s;
	packet.offset = 0;

	info = network_mysqld_masterinfo_new();

	err = err || network_mysqld_masterinfo_get(&packet, info);
	
	if (err) {
		network_mysqld_masterinfo_free(info);
		luaL_error(L, "%s: network_mysqld_masterinfo_get() failed", G_STRLOC);
		return 0;
	}

	lua_newtable(L);
        
        LUA_EXPORT_INT(info, master_lines);
	LUA_EXPORT_STR(info, master_log_file);
	LUA_EXPORT_INT(info, master_log_pos);
	LUA_EXPORT_STR(info, master_host);
	LUA_EXPORT_STR(info, master_user);
	LUA_EXPORT_STR(info, master_password);
	LUA_EXPORT_INT(info, master_port);
	LUA_EXPORT_INT(info, master_connect_retry);
	LUA_EXPORT_INT(info, master_ssl);
        LUA_EXPORT_STR(info, master_ssl_ca);
        LUA_EXPORT_STR(info, master_ssl_capath);
        LUA_EXPORT_STR(info, master_ssl_cert);
        LUA_EXPORT_STR(info, master_ssl_cipher);
        LUA_EXPORT_STR(info, master_ssl_key);
        if (info->master_lines >= 15) {
		LUA_EXPORT_INT(info, master_ssl_verify_server_cert);
	}
	
	network_mysqld_masterinfo_free(info);

	return 1;
}