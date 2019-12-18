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
struct cb_param {int callback; void* stream; int /*<<< orphan*/ * state; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  free (struct cb_param*) ; 
 int luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,struct cb_param*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * lua_topointer (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 struct cb_param* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stream_cb ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 void* taos_open_stream (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,struct cb_param*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l_open_stream(lua_State *L){
  int r = luaL_ref(L, LUA_REGISTRYINDEX);
  TAOS *    taos = lua_topointer(L,1);
  char * sqlstr = lua_tostring(L,2);
  int stime = luaL_checknumber(L,3);

  lua_newtable(L);
  int table_index = lua_gettop(L);

  struct cb_param *p = malloc(sizeof(struct cb_param));
  p->state = L;
  p->callback=r;
  //  printf("r:%d, L:%d\n",r,L);
  void * s = taos_open_stream(taos,sqlstr,stream_cb,stime,p,NULL);
  if (s == NULL) {
    printf("failed to open stream, reason:%s\n", taos_errstr(taos));
    free(p);
    lua_pushnumber(L, -1);
    lua_setfield(L, table_index, "code");
    lua_pushstring(L, taos_errstr(taos));
    lua_setfield(L, table_index, "error");
    lua_pushlightuserdata(L,NULL);
    lua_setfield(L, table_index, "stream");
  }else{
    //    printf("success to open stream\n");
    lua_pushnumber(L, 0);
    lua_setfield(L, table_index, "code");
    lua_pushstring(L, taos_errstr(taos));
    lua_setfield(L, table_index, "error");
    p->stream = s;
    lua_pushlightuserdata(L,p);
    lua_setfield(L, table_index, "stream");//stream has different content in lua and c.
  }

  return 1;
}