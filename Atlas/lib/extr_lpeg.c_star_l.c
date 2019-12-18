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
struct TYPE_3__ {int /*<<< orphan*/  cs; } ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  TYPE_1__ CharsetTag ;

/* Variables and functions */
 scalar_t__ ISCHARSET ; 
 int /*<<< orphan*/ * getpatt (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ isheadfail (int /*<<< orphan*/ *) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  optimizecaptures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optimizejumps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  optionalheadfail (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  optionals (int /*<<< orphan*/ *,int,int) ; 
 int repeatcharset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * repeatheadfail (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * repeats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ tocharset (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int star_l (lua_State *L) {
  int l1;
  int n = luaL_checkint(L, 2);
  Instruction *p1 = getpatt(L, 1, &l1);
  if (n >= 0) {
    CharsetTag st;
    Instruction *op;
    if (tocharset(p1, &st) == ISCHARSET)
      return repeatcharset(L, st.cs, l1, n);
    if (isheadfail(p1))
      op = repeatheadfail(L, l1, n);
    else
      op = repeats(L, p1, l1, n);
    optimizecaptures(op);
    optimizejumps(op);
  }
  else {
    if (isheadfail(p1))
      optionalheadfail(L, l1, -n);
    else
      optionals(L, l1, -n);
  }
  return 1;
}