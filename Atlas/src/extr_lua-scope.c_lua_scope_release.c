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
struct TYPE_3__ {scalar_t__ L_top; int /*<<< orphan*/  mutex; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ lua_scope ;

/* Variables and functions */
 int /*<<< orphan*/  g_critical (char*,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  g_mutex_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ lua_gettop (int /*<<< orphan*/ ) ; 

void lua_scope_release(lua_scope *sc, const char* pos) {
#ifdef HAVE_LUA_H
	if (lua_gettop(sc->L) != sc->L_top) {
		g_critical("%s: lua-stack out of sync: is %d, should be %d", pos, lua_gettop(sc->L), sc->L_top);
	}
#endif

	g_mutex_unlock(sc->mutex);
/*	g_warning("%s: --- released lua scope", pos); */

	return;
}