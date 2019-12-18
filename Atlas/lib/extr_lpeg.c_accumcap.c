#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  cap; int /*<<< orphan*/ * L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 scalar_t__ Cfunction ; 
 scalar_t__ captype (int /*<<< orphan*/ ) ; 
 scalar_t__ isclosecap (int /*<<< orphan*/ ) ; 
 scalar_t__ isfullcap (int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int pushallcaptures (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pushcapture (TYPE_1__*) ; 
 int /*<<< orphan*/  pushluaval (TYPE_1__*) ; 

__attribute__((used)) static int accumcap (CapState *cs) {
  lua_State *L = cs->L;
  if (isfullcap(cs->cap++) || isclosecap(cs->cap) || pushcapture(cs) != 1)
    return luaL_error(L, "no initial value for accumulator capture");
  while (!isclosecap(cs->cap)) {
    int n;
    if (captype(cs->cap) != Cfunction)
      return luaL_error(L, "invalid (non function) capture to accumulate");
    pushluaval(cs);
    lua_insert(L, -2);  /* put function before previous capture */
    n = pushallcaptures(cs, 0);
    lua_call(L, n + 1, 1);
  }
  cs->cap++;
  return 1;
}