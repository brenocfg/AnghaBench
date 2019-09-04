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

/* Variables and functions */
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  luaL_checkstack (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_optinteger (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t posrelat (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uchar (char const) ; 

__attribute__((used)) static int str_byte (lua_State *L) {
  size_t l;
  const char *s = luaL_checklstring(L, 1, &l);
  size_t posi = posrelat(luaL_optinteger(L, 2, 1), l);
  size_t pose = posrelat(luaL_optinteger(L, 3, posi), l);
  int n, i;
  if (posi < 1) posi = 1;
  if (pose > l) pose = l;
  if (posi > pose) return 0;  /* empty interval; return no values */
  n = (int)(pose -  posi + 1);
  if (posi + n <= pose)  /* (size_t -> int) overflow? */
    return luaL_error(L, "string slice too long");
  luaL_checkstack(L, n, "string slice too long");
  for (i=0; i<n; i++)
    lua_pushinteger(L, uchar(s[posi+i-1]));
  return n;
}