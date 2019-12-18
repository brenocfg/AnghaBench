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
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * taos_connect (char*,char*,char*,char*,int) ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_init () ; 

__attribute__((used)) static int l_connect(lua_State *L){
  TAOS *    taos;
  char *host = lua_tostring(L, 1);
  char *user = lua_tostring(L, 2);
  char *password = lua_tostring(L, 3);
  char *database = lua_tostring(L, 4);
  int port =luaL_checknumber(L, 5);
  taos_init();
  
  lua_newtable(L);
  int table_index = lua_gettop(L);

  taos = taos_connect(host, user,password,database, port);
  if (taos == NULL) {
    printf("failed to connect server, reason:%s\n", taos_errstr(taos));
    
    lua_pushnumber(L, -1);
    lua_setfield(L, table_index, "code");
    lua_pushstring(L, taos_errstr(taos));
    lua_setfield(L, table_index, "error");    
    lua_pushlightuserdata(L,NULL);
    lua_setfield(L, table_index, "conn");
  }else{
    printf("success to connect server\n");
    lua_pushnumber(L, 0);
    lua_setfield(L, table_index, "code");
    lua_pushstring(L, taos_errstr(taos));
    lua_setfield(L, table_index, "error");    
    lua_pushlightuserdata(L,taos);
    lua_setfield(L, table_index, "conn");
  }

  return 1;
}