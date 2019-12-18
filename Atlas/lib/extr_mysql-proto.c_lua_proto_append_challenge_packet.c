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
typedef  int /*<<< orphan*/  network_mysqld_auth_challenge ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_IMPORT_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_IMPORT_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  capabilities ; 
 int /*<<< orphan*/  challenge ; 
 int /*<<< orphan*/  charset ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_auth_challenge_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_mysqld_auth_challenge_new () ; 
 int /*<<< orphan*/  network_mysqld_proto_append_auth_challenge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protocol_version ; 
 int /*<<< orphan*/  server_status ; 
 int /*<<< orphan*/  server_version ; 
 int /*<<< orphan*/  thread_id ; 

__attribute__((used)) static int lua_proto_append_challenge_packet (lua_State *L) {
	GString *packet;
	network_mysqld_auth_challenge *auth_challenge;

	luaL_checktype(L, 1, LUA_TTABLE);

	auth_challenge = network_mysqld_auth_challenge_new();

	LUA_IMPORT_INT(auth_challenge, protocol_version);
	LUA_IMPORT_INT(auth_challenge, server_version);
	LUA_IMPORT_INT(auth_challenge, thread_id);
	LUA_IMPORT_INT(auth_challenge, capabilities);
	LUA_IMPORT_INT(auth_challenge, charset);
	LUA_IMPORT_INT(auth_challenge, server_status);

	LUA_IMPORT_STR(auth_challenge, challenge);

	packet = g_string_new(NULL);	
	network_mysqld_proto_append_auth_challenge(packet, auth_challenge);
	
	network_mysqld_auth_challenge_free(auth_challenge);

	lua_pushlstring(L, S(packet));
	
	g_string_free(packet, TRUE);

	return 1;
}