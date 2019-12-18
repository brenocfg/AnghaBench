#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_MULTRET ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int lua_gettop (int /*<<< orphan*/ ) ; 
 int pushallcaptures (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushluaval (TYPE_1__*) ; 

__attribute__((used)) static int functioncap (CapState *cs) {
  int n;
  int top = lua_gettop(cs->L);
  pushluaval(cs);
  n = pushallcaptures(cs, 0);
  lua_call(cs->L, n, LUA_MULTRET);
  return lua_gettop(cs->L) - top;
}