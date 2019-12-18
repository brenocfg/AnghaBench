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
struct TYPE_4__ {int /*<<< orphan*/  cap; int /*<<< orphan*/  L; } ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  isclosecap (int /*<<< orphan*/ ) ; 
 scalar_t__ isfullcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawseti (int /*<<< orphan*/ ,int,int) ; 
 int pushcapture (TYPE_1__*) ; 

__attribute__((used)) static int tablecap (CapState *cs) {
  int n = 0;
  lua_newtable(cs->L);
  if (isfullcap(cs->cap++))
    return 1;  /* table is empty */
  while (!isclosecap(cs->cap)) {
    int i;
    int k = pushcapture(cs);
    for (i = k; i > 0; i--)
      lua_rawseti(cs->L, -(i + 1), n + i);
    n += k;
  }
  cs->cap++;  /* skip close entry */
  return 1;
}