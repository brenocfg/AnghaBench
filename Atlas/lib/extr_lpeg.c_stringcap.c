#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  luaL_Buffer ;
struct TYPE_10__ {int /*<<< orphan*/  L; int /*<<< orphan*/  ptop; TYPE_1__* cap; } ;
struct TYPE_9__ {scalar_t__ s; scalar_t__ e; } ;
struct TYPE_8__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ StrAux ;
typedef  TYPE_3__ CapState ;

/* Variables and functions */
 int MAXSTRCAPS ; 
 int getstrcaps (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_addchar (int /*<<< orphan*/ *,char const) ; 
 int /*<<< orphan*/  luaL_addlstring (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ ,char*,char const) ; 
 char* lua_tolstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  subscache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updatecache (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stringcap (luaL_Buffer *b, CapState *cs) {
  StrAux cps[MAXSTRCAPS];
  int n;
  size_t len, i;
  const char *c;
  updatecache(cs, cs->cap->idx);
  c = lua_tolstring(cs->L, subscache(cs->ptop), &len);
  n = getstrcaps(cs, cps, 0) - 1;
  for (i = 0; i < len; i++) {
    if (c[i] != '%' || c[++i] < '0' || c[i] > '9')
      luaL_addchar(b, c[i]);
    else {
      int l = c[i] - '0';
      if (l > n)
        luaL_error(cs->L, "invalid capture index (%c)", c[i]);
      luaL_addlstring(b, cps[l].s, cps[l].e - cps[l].s);
    }
  }
}