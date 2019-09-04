#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  seed; } ;
typedef  int /*<<< orphan*/  TString ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 size_t LUAI_MAXSHORTLEN ; 
 int /*<<< orphan*/  LUA_TLNGSTR ; 
 int MAX_SIZET ; 
 int /*<<< orphan*/ * createstrobj (int /*<<< orphan*/ *,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * internshrstr (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  luaM_toobig (int /*<<< orphan*/ *) ; 

TString *luaS_newlstr (lua_State *L, const char *str, size_t l) {
  if (l <= LUAI_MAXSHORTLEN)  /* short string? */
    return internshrstr(L, str, l);
  else {
    if (l + 1 > (MAX_SIZET - sizeof(TString))/sizeof(char))
      luaM_toobig(L);
    return createstrobj(L, str, l, LUA_TLNGSTR, G(L)->seed, NULL);
  }
}