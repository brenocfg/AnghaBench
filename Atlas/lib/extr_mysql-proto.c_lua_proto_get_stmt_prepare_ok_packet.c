#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ offset; TYPE_2__* data; } ;
typedef  TYPE_1__ network_packet ;
typedef  int /*<<< orphan*/  network_mysqld_stmt_prepare_ok_packet_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {char* str; size_t len; } ;
typedef  TYPE_2__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  LUA_EXPORT_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 scalar_t__ network_mysqld_proto_get_stmt_prepare_ok_packet (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_stmt_prepare_ok_packet_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_mysqld_stmt_prepare_ok_packet_new () ; 
 int /*<<< orphan*/  num_columns ; 
 int /*<<< orphan*/  num_params ; 
 int /*<<< orphan*/  stmt_id ; 
 int /*<<< orphan*/  warnings ; 

__attribute__((used)) static int lua_proto_get_stmt_prepare_ok_packet (lua_State *L) {
	size_t packet_len;
	const char *packet_str = luaL_checklstring(L, 1, &packet_len);
	network_mysqld_stmt_prepare_ok_packet_t *cmd;
	network_packet packet;
	GString s;
	int err = 0;

	s.str = (char *)packet_str;
	s.len = packet_len;

	packet.data = &s;
	packet.offset = 0;

	cmd = network_mysqld_stmt_prepare_ok_packet_new();

	err = err || network_mysqld_proto_get_stmt_prepare_ok_packet(&packet, cmd);
	if (err) {
		network_mysqld_stmt_prepare_ok_packet_free(cmd);

		luaL_error(L, "%s: network_mysqld_proto_get_stmt_prepare_ok_packet() failed", G_STRLOC);
		return 0;
	}

	lua_newtable(L);

	LUA_EXPORT_INT(cmd, stmt_id);
	LUA_EXPORT_INT(cmd, num_columns);
	LUA_EXPORT_INT(cmd, num_params);
	LUA_EXPORT_INT(cmd, warnings);

	network_mysqld_stmt_prepare_ok_packet_free(cmd);

	return 1;
}