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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  gsize ;
struct TYPE_2__ {int /*<<< orphan*/  table; int /*<<< orphan*/  org_table; int /*<<< orphan*/  org_name; int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ MYSQL_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strleq (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_resultset_field_get(lua_State *L) {
	MYSQL_FIELD *field = *(MYSQL_FIELD **)luaL_checkself(L);
	gsize keysize = 0;
	const char *key = luaL_checklstring(L, 2, &keysize);
        
	if (strleq(key, keysize, C("type"))) {
		lua_pushinteger(L, field->type);
	} else if (strleq(key, keysize, C("name"))) {
		lua_pushstring(L, field->name);
	} else if (strleq(key, keysize, C("org_name"))) {
		lua_pushstring(L, field->org_name);
	} else if (strleq(key, keysize, C("org_table"))) {
		lua_pushstring(L, field->org_table);
	} else if (strleq(key, keysize, C("table"))) {
		lua_pushstring(L, field->table);
	} else {
		lua_pushnil(L);
	}
    
	return 1;
}