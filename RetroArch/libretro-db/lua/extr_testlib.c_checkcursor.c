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
typedef  void libretrodb_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 void* luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static libretrodb_cursor_t *checkcursor(lua_State *L)
{
	void *ud = luaL_checkudata(L, 1, "RarchDB.Cursor");
	luaL_argcheck(L, ud != NULL, 1, "`RarchDB.Cursor' expected");
	return ud;
}