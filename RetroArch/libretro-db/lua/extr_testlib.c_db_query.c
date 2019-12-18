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
typedef  int /*<<< orphan*/  libretrodb_query_t ;
typedef  int /*<<< orphan*/  libretrodb_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/ * checkdb (int /*<<< orphan*/ *) ; 
 int libretrodb_cursor_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * libretrodb_query_compile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  libretrodb_query_free (int /*<<< orphan*/ *) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_getmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 char const* strerror (int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int db_query(lua_State *L)
{
   libretrodb_t            *db = checkdb(L);
   const char           *query = luaL_checkstring(L, -1);
   const char           *error = NULL;
   libretrodb_query_t       *q = libretrodb_query_compile(
         db, query, strlen(query), &error);

   if (error)
   {
      lua_pushnil(L);
      lua_pushstring(L, error);
   }
   else
   {
      int rv;
      libretrodb_cursor_t *cursor = lua_newuserdata(L, sizeof(libretrodb_t));

      if ((rv = libretrodb_cursor_open(db, cursor, q)) == 0)
      {
         luaL_getmetatable(L, "RarchDB.Cursor");
         lua_setmetatable(L, -2);
         lua_pushnil(L);
      }
      else
      {
         lua_pop(L, 1);
         lua_pushnil(L);
         lua_pushstring(L, strerror(-rv));
      }
      libretrodb_query_free(q);
   }
   return 2;
}