#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* fields; } ;
typedef  TYPE_1__ proxy_resultset_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__* udata; } ;
typedef  TYPE_2__ GRef ;
typedef  TYPE_3__ GPtrArray ;

/* Variables and functions */
 scalar_t__ luaL_checkself (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proxy_resultset_fields_len(lua_State *L) {
	GRef *ref = *(GRef **)luaL_checkself(L);
	proxy_resultset_t *res = ref->udata;
	GPtrArray *fields = res->fields;
    lua_pushinteger(L, fields->len);
    return 1;
}