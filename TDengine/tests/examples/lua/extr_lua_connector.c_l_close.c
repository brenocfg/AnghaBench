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
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * lua_topointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  taos_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l_close(lua_State *L){
  TAOS *    taos= lua_topointer(L,1);
  lua_newtable(L);
  int table_index = lua_gettop(L);
  
  if(taos == NULL){
    lua_pushnumber(L, -1);
    lua_setfield(L, table_index, "code");    
    lua_pushstring(L, "null pointer.");
    lua_setfield(L, table_index, "error"); 
  }else{
    taos_close(taos);   
    lua_pushnumber(L, 0);
    lua_setfield(L, table_index, "code");    
    lua_pushstring(L, "done.");
    lua_setfield(L, table_index, "error");    
  }
  return 1;
}