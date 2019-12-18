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
typedef  int /*<<< orphan*/  lua_State ;
typedef  char int64_t ;
struct TYPE_3__ {char* name; int type; } ;
typedef  int /*<<< orphan*/ ** TAOS_ROW ;
typedef  int /*<<< orphan*/  TAOS_RES ;
typedef  TYPE_1__ TAOS_FIELD ;
typedef  int /*<<< orphan*/  TAOS ;

/* Variables and functions */
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
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_topointer (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int taos_affected_rows (int /*<<< orphan*/ *) ; 
 char* taos_errstr (int /*<<< orphan*/ *) ; 
 TYPE_1__* taos_fetch_fields (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** taos_fetch_row (int /*<<< orphan*/ *) ; 
 int taos_field_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taos_free_result (int /*<<< orphan*/ *) ; 
 scalar_t__ taos_query (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * taos_use_result (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l_query(lua_State *L){
  TAOS *    taos= lua_topointer(L,1);
  char *s = lua_tostring(L, 2);
  TAOS_RES *result;
  lua_newtable(L);
  int table_index = lua_gettop(L);

  //  printf("receive command:%s\r\n",s);
  if(taos_query(taos, s)!=0){
    printf("failed, reason:%s\n", taos_errstr(taos));
    lua_pushnumber(L, -1);
    lua_setfield(L, table_index, "code");    
    lua_pushstring(L, taos_errstr(taos));
    lua_setfield(L, table_index, "error");    
   
    return 1;
    
  }else{
    //printf("success to query.\n");
    result = taos_use_result(taos);

    if (result == NULL) {
      printf("failed to get result, reason:%s\n", taos_errstr(taos));
      lua_pushnumber(L, -2);
      lua_setfield(L, table_index, "code");    
      lua_pushstring(L, taos_errstr(taos));
      lua_setfield(L, table_index, "error");    
      return 1;
    }

    TAOS_ROW    row;
    int         rows = 0;
    int         num_fields = taos_field_count(taos);
    TAOS_FIELD *fields = taos_fetch_fields(result);
    char        temp[256];

    int affectRows = taos_affected_rows(taos);
    //    printf(" affect rows:%d\r\n", affectRows);
    lua_pushnumber(L, 0);
    lua_setfield(L, table_index, "code");
    lua_pushinteger(L, affectRows);
    lua_setfield(L, table_index, "affected");
    lua_newtable(L);
    
    while ((row = taos_fetch_row(result))) {
      //printf("row index:%d\n",rows);
      rows++;

      lua_pushnumber(L,rows);
      lua_newtable(L);

      for (int i = 0; i < num_fields; ++i) {
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

	lua_settable(L,-3);
      }

      lua_settable(L,-3);
    }
    taos_free_result(result);    
  }

  lua_setfield(L, table_index, "item");
  return 1;
}