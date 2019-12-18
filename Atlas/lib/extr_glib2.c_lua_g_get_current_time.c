#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  TYPE_1__ GTimeVal ;

/* Variables and functions */
 int /*<<< orphan*/  g_get_current_time (TYPE_1__*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 

__attribute__((used)) static int lua_g_get_current_time (lua_State *L) {
	GTimeVal t;

	g_get_current_time(&t);

	lua_newtable(L);
	lua_pushinteger(L, t.tv_sec);
	lua_setfield(L, -2, "tv_sec");
	lua_pushinteger(L, t.tv_usec);
	lua_setfield(L, -2, "tv_usec");

	return 1;
}