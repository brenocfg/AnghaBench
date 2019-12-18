#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {char const* s; int ptop; scalar_t__ valuecached; int /*<<< orphan*/ * L; TYPE_1__* cap; TYPE_1__* ocap; } ;
struct TYPE_10__ {char const* s; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ Capture ;
typedef  TYPE_2__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  Cclose ; 
 scalar_t__ Cruntime ; 
 int /*<<< orphan*/  LUA_MULTRET ; 
 int /*<<< orphan*/  SUBJIDX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ captype (TYPE_1__*) ; 
 TYPE_1__* findopen (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pushallcaptures (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pushluaval (TYPE_2__*) ; 

__attribute__((used)) static int runtimecap (lua_State *L, Capture *close, Capture *ocap,
                       const char *o, const char *s, int ptop) {
  CapState cs;
  int n;
  Capture *open = findopen(close);
  assert(captype(open) == Cruntime);
  close->kind = Cclose;
  close->s = s;
  cs.ocap = ocap; cs.cap = open; cs.L = L;
  cs.s = o; cs.valuecached = 0; cs.ptop = ptop;
  luaL_checkstack(L, 4, "too many runtime captures");
  pushluaval(&cs);
  lua_pushvalue(L, SUBJIDX);  /* push original subject */
  lua_pushinteger(L, s - o + 1);  /* current position */
  n = pushallcaptures(&cs, 0);
  lua_call(L, n + 2, LUA_MULTRET);
  return close - open;
}