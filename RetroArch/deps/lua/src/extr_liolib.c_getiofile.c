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
struct TYPE_3__ {int /*<<< orphan*/ * f; } ;
typedef  TYPE_1__ LStream ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int IOPREF_LEN ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 scalar_t__ isclosed (TYPE_1__*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static FILE *getiofile (lua_State *L, const char *findex) {
  LStream *p;
  lua_getfield(L, LUA_REGISTRYINDEX, findex);
  p = (LStream *)lua_touserdata(L, -1);
  if (isclosed(p))
    luaL_error(L, "standard %s file is closed", findex + IOPREF_LEN);
  return p->f;
}