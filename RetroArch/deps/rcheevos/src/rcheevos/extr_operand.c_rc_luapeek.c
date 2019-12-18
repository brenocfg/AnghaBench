#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int (* peek ) (unsigned int,unsigned int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ud; } ;
typedef  TYPE_1__ rc_luapeek_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 unsigned int stub1 (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rc_luapeek(lua_State* L) {
  unsigned address = (unsigned)luaL_checkinteger(L, 1);
  unsigned num_bytes = (unsigned)luaL_checkinteger(L, 2);
  rc_luapeek_t* luapeek = (rc_luapeek_t*)lua_touserdata(L, 3);

  unsigned value = luapeek->peek(address, num_bytes, luapeek->ud);

  lua_pushinteger(L, value);
  return 1;
}