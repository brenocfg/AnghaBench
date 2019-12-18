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
typedef  int /*<<< orphan*/  libretrodb_t ;

/* Variables and functions */
 int libretrodb_open (char const*,int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static int db_new(lua_State *L)
{
   libretrodb_t *db = NULL;
   const char *db_file = NULL;
   int rv;
   db_file = luaL_checkstring(L, -1);
   db = lua_newuserdata(L, sizeof(libretrodb_t));
   if ((rv = libretrodb_open(db_file, db)) == 0)
   {
      luaL_getmetatable(L, "RarchDB.DB");
      lua_setmetatable(L, -2);
      lua_pushnil(L);
   }
   else
   {
      lua_pop(L, 1);
      lua_pushnil(L);
      lua_pushstring(L, strerror(-rv));
   }
   return 2;
}