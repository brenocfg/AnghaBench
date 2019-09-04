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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int LUAI_MAXNUMBER2STR ; 
 int /*<<< orphan*/  luaS_newlstr (int /*<<< orphan*/ *,char*,int) ; 
 int lua_number2str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsvalue2s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttisnumber (int /*<<< orphan*/ ) ; 

int luaV_tostring (lua_State *L, StkId obj) {
  if (!ttisnumber(obj))
    return 0;
  else {
    char s[LUAI_MAXNUMBER2STR];
    lua_Number n = nvalue(obj);
    int l = lua_number2str(s, n);
    setsvalue2s(L, obj, luaS_newlstr(L, s, l));
    return 1;
  }
}