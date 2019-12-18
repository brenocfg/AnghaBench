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
typedef  int /*<<< orphan*/  GQueue ;

/* Variables and functions */
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_injection_queue_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proxy_queue_reset(lua_State *L) {
	/* we expect 2 parameters */
	GQueue *q = *(GQueue **)luaL_checkself(L);

	network_injection_queue_reset(q);
    
	return 0;
}