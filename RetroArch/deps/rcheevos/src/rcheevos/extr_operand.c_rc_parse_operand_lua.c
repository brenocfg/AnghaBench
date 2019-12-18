#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ L; int /*<<< orphan*/  funcs_ndx; } ;
typedef  TYPE_2__ rc_parse_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  luafunc; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_1__ value; } ;
typedef  TYPE_3__ rc_operand_t ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int RC_INVALID_LUA_OPERAND ; 
 int RC_OK ; 
 int /*<<< orphan*/  RC_OPERAND_LUA ; 
 scalar_t__ isalnum (char const) ; 
 int /*<<< orphan*/  isalpha (char const) ; 
 int /*<<< orphan*/  luaL_ref (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_gettable (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isfunction (scalar_t__,int) ; 
 int /*<<< orphan*/  lua_istable (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (scalar_t__,int) ; 
 int /*<<< orphan*/  lua_pushlstring (scalar_t__,char const*,int) ; 

__attribute__((used)) static int rc_parse_operand_lua(rc_operand_t* self, const char** memaddr, rc_parse_state_t* parse) {
  const char* aux = *memaddr;
#ifndef RC_DISABLE_LUA
  const char* id;
#endif

  if (*aux++ != '@') {
    return RC_INVALID_LUA_OPERAND;
  }

  if (!isalpha(*aux)) {
    return RC_INVALID_LUA_OPERAND;
  }

#ifndef RC_DISABLE_LUA
  id = aux;
#endif

  while (isalnum(*aux) || *aux == '_') {
    aux++;
  }

#ifndef RC_DISABLE_LUA

  if (parse->L != 0) {
    if (!lua_istable(parse->L, parse->funcs_ndx)) {
      return RC_INVALID_LUA_OPERAND;
    }

    lua_pushlstring(parse->L, id, aux - id);
    lua_gettable(parse->L, parse->funcs_ndx);

    if (!lua_isfunction(parse->L, -1)) {
      lua_pop(parse->L, 1);
      return RC_INVALID_LUA_OPERAND;
    }

    self->value.luafunc = luaL_ref(parse->L, LUA_REGISTRYINDEX);
  }

#endif /* RC_DISABLE_LUA */

  self->type = RC_OPERAND_LUA;
  *memaddr = aux;
  return RC_OK;
}