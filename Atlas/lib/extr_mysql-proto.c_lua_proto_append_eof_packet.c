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
typedef  int /*<<< orphan*/  network_mysqld_eof_packet_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_IMPORT_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_eof_packet_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_mysqld_eof_packet_new () ; 
 int /*<<< orphan*/  network_mysqld_proto_append_eof_packet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_status ; 
 int /*<<< orphan*/  warnings ; 

__attribute__((used)) static int lua_proto_append_eof_packet (lua_State *L) {
	GString *packet;
	network_mysqld_eof_packet_t *eof_packet;

	luaL_checktype(L, 1, LUA_TTABLE);

	eof_packet = network_mysqld_eof_packet_new();

	LUA_IMPORT_INT(eof_packet, server_status);
	LUA_IMPORT_INT(eof_packet, warnings);

	packet = g_string_new(NULL);	
	network_mysqld_proto_append_eof_packet(packet, eof_packet);

	network_mysqld_eof_packet_free(eof_packet);
	
	lua_pushlstring(L, S(packet));
	
	g_string_free(packet, TRUE);

	return 1;
}