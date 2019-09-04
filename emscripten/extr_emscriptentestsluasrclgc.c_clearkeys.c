#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_5__ {int /*<<< orphan*/ * gclist; } ;
typedef  TYPE_1__ Table ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* gco2t (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gnodelast (TYPE_1__*) ; 
 int /*<<< orphan*/  gval (int /*<<< orphan*/ *) ; 
 scalar_t__ iscleared (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removeentry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clearkeys (global_State *g, GCObject *l, GCObject *f) {
  for (; l != f; l = gco2t(l)->gclist) {
    Table *h = gco2t(l);
    Node *n, *limit = gnodelast(h);
    for (n = gnode(h, 0); n < limit; n++) {
      if (!ttisnil(gval(n)) && (iscleared(g, gkey(n)))) {
        setnilvalue(gval(n));  /* remove value ... */
        removeentry(n);  /* and remove entry from table */
      }
    }
  }
}