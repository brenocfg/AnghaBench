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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int /*<<< orphan*/  S (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_proto_password_unscramble (int /*<<< orphan*/ *,char const*,size_t,char const*,size_t,char const*,size_t) ; 

__attribute__((used)) static int lua_password_unscramble(lua_State *L) {
	size_t challenge_len;
	const char *challenge = luaL_checklstring(L, 1, &challenge_len);
	size_t response_len;
	const char *response = luaL_checklstring(L, 2, &response_len);
	size_t dbl_hashed_password_len;
	const char *dbl_hashed_password = luaL_checklstring(L, 3, &dbl_hashed_password_len);

	GString *hashed_password = g_string_new(NULL);

	network_mysqld_proto_password_unscramble(
			hashed_password,
			challenge, challenge_len,
			response, response_len,
			dbl_hashed_password, dbl_hashed_password_len);
	
	lua_pushlstring(L, S(hashed_password));

	g_string_free(hashed_password, TRUE);
	
	return 1;
}