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
typedef  int /*<<< orphan*/  b_uint ;

/* Variables and functions */
 int /*<<< orphan*/  andaux (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushunsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int b_and (lua_State *L) {
  b_uint r = andaux(L);
  lua_pushunsigned(L, r);
  return 1;
}