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
 unsigned int crc32 (char const*,size_t) ; 
 int /*<<< orphan*/  g_debug (char*,...) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,unsigned int) ; 

int crc32_string(lua_State *L) {
	size_t str_len;
	const char *str = luaL_checklstring(L, 1, &str_len);
    g_debug("string:%s, length:%d", str, str_len);
    // crc32 hash
	unsigned int key = crc32(str, str_len);
    g_debug("crc key:%ld", key);

    // push crc number
    lua_pushnumber(L, key);

    return 1;
}