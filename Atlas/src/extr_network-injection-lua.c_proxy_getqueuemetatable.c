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
 int /*<<< orphan*/  methods_proxy_queue ; 
 int /*<<< orphan*/  proxy_getmetatable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void proxy_getqueuemetatable(lua_State *L) {
    proxy_getmetatable(L, methods_proxy_queue);
}