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
typedef  int /*<<< orphan*/  tokens ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  GPtrArray ;

/* Variables and functions */
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/ ** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sql_tokenizer (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  sql_tokenizer_lua_getmetatable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sql_tokens_new () ; 

int proxy_tokenize(lua_State *L) {
	size_t str_len;
	const char *str = luaL_checklstring(L, 1, &str_len);
	GPtrArray *tokens = sql_tokens_new();
	GPtrArray **tokens_p;

	sql_tokenizer(tokens, str, str_len);

	tokens_p = lua_newuserdata(L, sizeof(tokens));                          /* (sp += 1) */
	*tokens_p = tokens;

	sql_tokenizer_lua_getmetatable(L);
	lua_setmetatable(L, -2);          /* tie the metatable to the udata   (sp -= 1) */

	return 1;
}