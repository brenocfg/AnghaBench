#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* ci; } ;
typedef  TYPE_2__ lua_State ;
struct TYPE_8__ {int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  api_checkvalidindex (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clCvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * index2addr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  luaC_barrier (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setobj (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void moveto (lua_State *L, TValue *fr, int idx) {
  TValue *to = index2addr(L, idx);
  api_checkvalidindex(L, to);
  setobj(L, to, fr);
  if (idx < LUA_REGISTRYINDEX)  /* function upvalue? */
    luaC_barrier(L, clCvalue(L->ci->func), fr);
  /* LUA_REGISTRYINDEX does not need gc barrier
     (collector revisits it before finishing collection) */
}