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
struct TYPE_3__ {int /*<<< orphan*/  L; int /*<<< orphan*/ * ocap; } ;
typedef  int /*<<< orphan*/  Capture ;
typedef  TYPE_1__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * findopen (int /*<<< orphan*/ *) ; 
 scalar_t__ isclosecap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isfullcap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static Capture *findback (CapState *cs, Capture *cap, int n) {
  int i;
  for (i = 0; i < n; i++) {
    if (cap == cs->ocap)
      luaL_error(cs->L, "invalid back reference (%d)", n);
    cap--;
    if (isclosecap(cap))
      cap = findopen(cap);
    else if (!isfullcap(cap))
      i--;  /* does not count enclosing captures */
  }
  assert(!isclosecap(cap));
  return cap;
}