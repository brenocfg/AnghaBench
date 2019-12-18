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
typedef  int /*<<< orphan*/  GPtrArray ;

/* Variables and functions */
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sql_tokens_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int proxy_tokenize_gc(lua_State *L) {
	GPtrArray *tokens = *(GPtrArray **)luaL_checkself(L); 

	sql_tokens_free(tokens);

	return 0;
}