#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  L; int /*<<< orphan*/  ptop; TYPE_1__* cap; } ;
struct TYPE_6__ {int idx; } ;
typedef  TYPE_2__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ ,int) ; 
 int pushallcaptures (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subscache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updatecache (TYPE_2__*,int) ; 

__attribute__((used)) static int querycap (CapState *cs) {
  int idx = cs->cap->idx;
  int n = pushallcaptures(cs, 0);
  if (n > 1)  /* extra captures? */
    lua_pop(cs->L, n - 1);  /* throw them away */
  updatecache(cs, idx);
  lua_gettable(cs->L, subscache(cs->ptop));
  if (!lua_isnil(cs->L, -1))
    return 1;
  else {
    lua_pop(cs->L, 1);  /* remove value */
    return 0;
  }
}