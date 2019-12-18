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
struct TYPE_2__ {int /*<<< orphan*/  token_id; int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ sql_token ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 int /*<<< orphan*/  S (int /*<<< orphan*/ ) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,...) ; 
 char* sql_token_get_name (int /*<<< orphan*/ ,size_t*) ; 
 scalar_t__ strleq (char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_tokenize_token_get(lua_State *L) {
	sql_token *token = *(sql_token **)luaL_checkself(L); 
	size_t keysize;
	const char *key = luaL_checklstring(L, 2, &keysize);

    /* TODO: Fix bug
     *  token->text->len may be a large number, lua_pushlstring() would be crash
     *
     */
    //if(0 == lua_checkstack(L, token->text->len))
    //return 0;

    if (strleq(key, keysize, C("text"))) {
        lua_pushlstring(L, S(token->text));
        return 1;
    } else if (strleq(key, keysize, C("token_id"))) {
        lua_pushinteger(L, token->token_id);
        return 1;
    } else if (strleq(key, keysize, C("token_name"))) {
        size_t token_name_len = 0;
        const char *token_name = sql_token_get_name(token->token_id, &token_name_len);
        lua_pushlstring(L, token_name, token_name_len);
        return 1;
    } else {
        luaL_error(L, "tokens[...] has no %s field", key);
    }

	return 0;
}