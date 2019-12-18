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
typedef  int /*<<< orphan*/  network_mysqld_auth_response ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_IMPORT_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_IMPORT_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LUA_TTABLE ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  capabilities ; 
 int /*<<< orphan*/  charset ; 
 int /*<<< orphan*/  database ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_checktype (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_packet_size ; 
 int /*<<< orphan*/  network_mysqld_auth_response_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * network_mysqld_auth_response_new () ; 
 scalar_t__ network_mysqld_proto_append_auth_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  response ; 
 int /*<<< orphan*/  username ; 

__attribute__((used)) static int lua_proto_append_response_packet (lua_State *L) {
	GString *packet;
	network_mysqld_auth_response *auth_response;

	luaL_checktype(L, 1, LUA_TTABLE);

	packet = g_string_new(NULL);	
	auth_response = network_mysqld_auth_response_new();

	LUA_IMPORT_INT(auth_response, capabilities);
	LUA_IMPORT_INT(auth_response, max_packet_size);
	LUA_IMPORT_INT(auth_response, charset);

	LUA_IMPORT_STR(auth_response, username);
	LUA_IMPORT_STR(auth_response, response);
	LUA_IMPORT_STR(auth_response, database);

	if (network_mysqld_proto_append_auth_response(packet, auth_response)) {
		network_mysqld_auth_response_free(auth_response);
		g_string_free(packet, TRUE);

		luaL_error(L, "to_response_packet() failed");
        g_string_free(packet, TRUE);
		return 0;
	}
	
	network_mysqld_auth_response_free(auth_response);

	lua_pushlstring(L, S(packet));
	
	g_string_free(packet, TRUE);

	return 1;
}