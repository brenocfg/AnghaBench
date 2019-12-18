#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int byte ;
struct TYPE_4__ {int /*<<< orphan*/  buff; } ;
typedef  TYPE_1__ Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  correctset (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 TYPE_1__* newcharset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setchar (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int range_l (lua_State *L) {
  int arg;
  int top = lua_gettop(L);
  Instruction *p = newcharset(L);
  for (arg = 1; arg <= top; arg++) {
    int c;
    size_t l;
    const char *r = luaL_checklstring(L, arg, &l);
    luaL_argcheck(L, l == 2, arg, "range must have two characters");
    for (c = (byte)r[0]; c <= (byte)r[1]; c++)
      setchar(p[1].buff, c);
  }
  correctset(p);
  return 1;
}