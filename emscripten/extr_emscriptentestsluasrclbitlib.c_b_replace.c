#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int b_uint ;

/* Variables and functions */
 int fieldargs (int /*<<< orphan*/ *,int,int*) ; 
 int luaL_checkunsigned (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushunsigned (int /*<<< orphan*/ *,int) ; 
 int mask (int) ; 

__attribute__((used)) static int b_replace (lua_State *L) {
  int w;
  b_uint r = luaL_checkunsigned(L, 1);
  b_uint v = luaL_checkunsigned(L, 2);
  int f = fieldargs(L, 3, &w);
  int m = mask(w);
  v &= m;  /* erase bits outside given width */
  r = (r & ~(m << f)) | (v << f);
  lua_pushunsigned(L, r);
  return 1;
}