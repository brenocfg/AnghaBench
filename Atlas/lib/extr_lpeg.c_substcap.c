#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_9__ {char* s; } ;
struct TYPE_8__ {TYPE_5__* cap; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 scalar_t__ Cstring ; 
 scalar_t__ captype (TYPE_5__*) ; 
 char* closeaddr (TYPE_5__*) ; 
 int /*<<< orphan*/  isclosecap (TYPE_5__*) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  luaL_addvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 int pushcapture (TYPE_1__*) ; 
 int /*<<< orphan*/  stringcap (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void substcap (CapState *cs) {
  luaL_Buffer b;
  const char *curr = (cs->cap - 1)->s;
  luaL_buffinit(cs->L, &b);
  while (!isclosecap(cs->cap)) {
    int n;
    const char *next = cs->cap->s;
    luaL_addlstring(&b, curr, next - curr);
    if (captype(cs->cap) == Cstring)
      stringcap(&b, cs);  /* add capture directly to buffer */
    else if ((n = pushcapture(cs)) == 0) {  /* no capture? */
      curr = next;  /* result keeps the original text */
      continue;
    }
    else {
      if (n > 1) lua_pop(cs->L, n - 1);  /* ignore extra values */
      if (!lua_isstring(cs->L, -1))
        luaL_error(cs->L, "invalid replacement value (a %s)",
                          luaL_typename(cs->L, -1));
      luaL_addvalue(&b);  /* add result to accumulator */
    }
    /* continue after match */
    curr = closeaddr(cs->cap - 1);
  }
  luaL_addlstring(&b, curr, cs->cap->s - curr);
  luaL_pushresult(&b);
  cs->cap++;
}