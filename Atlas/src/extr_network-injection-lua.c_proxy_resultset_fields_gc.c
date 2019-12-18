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
typedef  int /*<<< orphan*/  GRef ;

/* Variables and functions */
 int /*<<< orphan*/  g_ref_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proxy_resultset_fields_gc(lua_State *L) {
	GRef *ref = *(GRef **)luaL_checkself(L);

	g_ref_unref(ref);
    
	return 0;
}