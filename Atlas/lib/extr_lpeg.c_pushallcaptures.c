#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* cap; int /*<<< orphan*/  L; } ;
struct TYPE_8__ {scalar_t__ s; } ;
typedef  TYPE_1__ Capture ;
typedef  TYPE_2__ CapState ;

/* Variables and functions */
 int /*<<< orphan*/  isclosecap (TYPE_1__*) ; 
 scalar_t__ isfullcap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ pushcapture (TYPE_2__*) ; 
 int /*<<< orphan*/  pushsubject (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int pushallcaptures (CapState *cs, int addextra) {
  Capture *co = cs->cap;
  int n = 0;
  if (isfullcap(cs->cap++)) {
    pushsubject(cs, co);  /* push whole match */
    return 1;
  }
  while (!isclosecap(cs->cap))
    n += pushcapture(cs);
  if (addextra || n == 0) {  /* need extra? */
    lua_pushlstring(cs->L, co->s, cs->cap->s - co->s);  /* push whole match */
    n++;
  }
  cs->cap++;  /* skip close entry */
  return n;
}