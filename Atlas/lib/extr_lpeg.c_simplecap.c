#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ ,int) ; 
 int pushallcaptures (TYPE_1__*,int) ; 

__attribute__((used)) static int simplecap (CapState *cs) {
  int n;
  lua_pushnil(cs->L);  /* open space */
  n = pushallcaptures(cs, 1);
  lua_replace(cs->L, -(n + 1));  /* put extra in previously opened slot */
  return n;
}