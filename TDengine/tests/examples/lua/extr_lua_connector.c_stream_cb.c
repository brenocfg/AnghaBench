#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cb_param {int /*<<< orphan*/  callback; int /*<<< orphan*/ * state; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  char int64_t ;
struct TYPE_3__ {char* name; int type; } ;
typedef  int /*<<< orphan*/ ** TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ TAOS_FIELD ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  TSDB_DATA_TYPE_BIGINT 137 
#define  TSDB_DATA_TYPE_BINARY 136 
#define  TSDB_DATA_TYPE_BOOL 135 
#define  TSDB_DATA_TYPE_DOUBLE 134 
#define  TSDB_DATA_TYPE_FLOAT 133 
#define  TSDB_DATA_TYPE_INT 132 
#define  TSDB_DATA_TYPE_NCHAR 131 
#define  TSDB_DATA_TYPE_SMALLINT 130 
#define  TSDB_DATA_TYPE_TIMESTAMP 129 
#define  TSDB_DATA_TYPE_TINYINT 128 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int taos_num_fields (int /*<<< orphan*/ *) ; 

void stream_cb(void *param, TAOS_RES *result, TAOS_ROW row){

  struct cb_param* p = (struct cb_param*) param;
  TAOS_FIELD *fields = taos_fetch_fields(result);
  int         numFields = taos_num_fields(result);

  printf("\n\r-----------------------------------------------------------------------------------\n");

  // printf("r:%d, L:%d\n",p->callback, p->state);

  lua_State *L = p->state;
  lua_rawgeti(L, LUA_REGISTRYINDEX, p->callback);

  lua_newtable(L);

  for (int i = 0; i < numFields; ++i) {
    if (row[i] == NULL) {
      continue;
    }

    lua_pushstring(L,fields[i].name);

    switch (fields[i].type) {
    case TSDB_DATA_TYPE_TINYINT:
      lua_pushinteger(L,*((char *)row[i]));
      break;
    case TSDB_DATA_TYPE_SMALLINT:
      lua_pushinteger(L,*((short *)row[i]));
      break;
    case TSDB_DATA_TYPE_INT:
      lua_pushinteger(L,*((int *)row[i]));
      break;
    case TSDB_DATA_TYPE_BIGINT:
      lua_pushinteger(L,*((int64_t *)row[i]));
      break;
    case TSDB_DATA_TYPE_FLOAT:
      lua_pushnumber(L,*((float *)row[i]));
      break;
    case TSDB_DATA_TYPE_DOUBLE:
      lua_pushnumber(L,*((double *)row[i]));
      break;
    case TSDB_DATA_TYPE_BINARY:
    case TSDB_DATA_TYPE_NCHAR:
      lua_pushstring(L,(char *)row[i]);
      break;
    case TSDB_DATA_TYPE_TIMESTAMP:
      lua_pushinteger(L,*((int64_t *)row[i]));
      break;
    case TSDB_DATA_TYPE_BOOL:
      lua_pushinteger(L,*((char *)row[i]));
      break;
    default:
      lua_pushnil(L);
      break;
    }

    lua_settable(L, -3);
  }

  lua_call(L, 1, 0);

  printf("-----------------------------------------------------------------------------------\n\r");
}