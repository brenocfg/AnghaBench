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
typedef  int /*<<< orphan*/  token ;
typedef  int /*<<< orphan*/  sql_token ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/ ** pdata; } ;
typedef  TYPE_1__ GPtrArray ;

/* Variables and functions */
 scalar_t__ G_MAXINT ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sql_tokenizer_lua_token_getmetatable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proxy_tokenize_get(lua_State *L) {
	GPtrArray *tokens = *(GPtrArray **)luaL_checkself(L); 
	int ndx = luaL_checkinteger(L, 2);
	sql_token *token;
	sql_token **token_p;

	if (tokens->len > G_MAXINT) {
		return 0;
	}

	/* lua uses 1 is starting index */
	if (ndx < 1 || ndx > (int)tokens->len) {
		return 0;
	}

	token = tokens->pdata[ndx - 1];
	if (NULL == token) {
		lua_pushnil(L);

		return 1;
	}

	token_p = lua_newuserdata(L, sizeof(token));                          /* (sp += 1) */
	*token_p = token;

	sql_tokenizer_lua_token_getmetatable(L);
	lua_setmetatable(L, -2);             /* tie the metatable to the udata   (sp -= 1) */

	return 1;
}