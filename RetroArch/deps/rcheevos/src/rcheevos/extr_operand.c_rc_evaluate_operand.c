#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_8__ {unsigned int num; TYPE_1__* memref; int /*<<< orphan*/  luafunc; } ;
struct TYPE_9__ {int type; TYPE_2__ value; } ;
typedef  TYPE_3__ rc_operand_t ;
struct TYPE_10__ {void* ud; int /*<<< orphan*/  peek; } ;
typedef  TYPE_4__ rc_luapeek_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {unsigned int value; unsigned int previous; unsigned int prior; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_OK ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
#define  RC_OPERAND_ADDRESS 133 
#define  RC_OPERAND_CONST 132 
#define  RC_OPERAND_DELTA 131 
#define  RC_OPERAND_FP 130 
#define  RC_OPERAND_LUA 129 
#define  RC_OPERAND_PRIOR 128 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rc_luapeek ; 

unsigned rc_evaluate_operand(rc_operand_t* self, rc_peek_t peek, void* ud, lua_State* L) {
#ifndef RC_DISABLE_LUA
  rc_luapeek_t luapeek;
#endif /* RC_DISABLE_LUA */

  unsigned value = 0;

  switch (self->type) {
    case RC_OPERAND_CONST:
      value = self->value.num;
      break;

    case RC_OPERAND_FP:
      /* This is handled by rc_evaluate_expression. */
      return 0;
    
    case RC_OPERAND_LUA:
#ifndef RC_DISABLE_LUA

      if (L != 0) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, self->value.luafunc);
        lua_pushcfunction(L, rc_luapeek);

        luapeek.peek = peek;
        luapeek.ud = ud;

        lua_pushlightuserdata(L, &luapeek);
        
        if (lua_pcall(L, 2, 1, 0) == LUA_OK) {
          if (lua_isboolean(L, -1)) {
            value = lua_toboolean(L, -1);
          }
          else {
            value = (unsigned)lua_tonumber(L, -1);
          }
        }

        lua_pop(L, 1);
      }

#endif /* RC_DISABLE_LUA */

      break;

    case RC_OPERAND_ADDRESS:
      value = self->value.memref->value;
      break;

    case RC_OPERAND_DELTA:
      value = self->value.memref->previous;
      break;

    case RC_OPERAND_PRIOR:
      value = self->value.memref->prior;
      break;
  }

  return value;
}