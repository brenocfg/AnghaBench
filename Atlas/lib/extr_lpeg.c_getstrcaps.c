#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  s; } ;
struct TYPE_9__ {TYPE_3__* cap; int /*<<< orphan*/  L; } ;
struct TYPE_8__ {int /*<<< orphan*/  e; int /*<<< orphan*/  s; } ;
typedef  TYPE_1__ StrAux ;
typedef  TYPE_2__ CapState ;

/* Variables and functions */
 scalar_t__ Csimple ; 
 int MAXSTRCAPS ; 
 scalar_t__ captype (TYPE_3__*) ; 
 int /*<<< orphan*/  closeaddr (TYPE_3__*) ; 
 int /*<<< orphan*/  isclosecap (TYPE_3__*) ; 
 int /*<<< orphan*/  isfullcap (int /*<<< orphan*/ ) ; 
 int luaL_error (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int getstrcaps (CapState *cs, StrAux *cps, int n) {
  int k = n++;
  if (k < MAXSTRCAPS) cps[k].s = cs->cap->s;
  if (!isfullcap(cs->cap++)) {
    while (!isclosecap(cs->cap)) {
      if (captype(cs->cap) != Csimple)
        return luaL_error(cs->L,
                          "invalid capture #%d in replacement pattern", n);
      n = getstrcaps(cs, cps, n);
    }
    cs->cap++;  /* skip close */
  }
  if (k < MAXSTRCAPS) cps[k].e = closeaddr(cs->cap - 1);
  return n;
}