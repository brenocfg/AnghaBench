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
 int /*<<< orphan*/  IO_OUTPUT ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int aux_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isnone (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tofile (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int io_close (lua_State *L) {
  if (lua_isnone(L, 1))  /* no argument? */
    lua_getfield(L, LUA_REGISTRYINDEX, IO_OUTPUT);  /* use standard output */
  tofile(L);  /* make sure argument is an open stream */
  return aux_close(L);
}