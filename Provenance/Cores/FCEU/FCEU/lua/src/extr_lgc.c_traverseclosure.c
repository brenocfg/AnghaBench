#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  global_State ;
struct TYPE_9__ {int nups; } ;
struct TYPE_7__ {int nupvalues; TYPE_5__** upvals; TYPE_5__* p; } ;
struct TYPE_6__ {int nupvalues; int /*<<< orphan*/ * upvalue; scalar_t__ isC; TYPE_5__* env; } ;
struct TYPE_8__ {TYPE_2__ l; TYPE_1__ c; } ;
typedef  TYPE_3__ Closure ;

/* Variables and functions */
 int /*<<< orphan*/  lua_assert (int) ; 
 int /*<<< orphan*/  markobject (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  markvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void traverseclosure (global_State *g, Closure *cl) {
  markobject(g, cl->c.env);
  if (cl->c.isC) {
    int i;
    for (i=0; i<cl->c.nupvalues; i++)  /* mark its upvalues */
      markvalue(g, &cl->c.upvalue[i]);
  }
  else {
    int i;
    lua_assert(cl->l.nupvalues == cl->l.p->nups);
    markobject(g, cl->l.p);
    for (i=0; i<cl->l.nupvalues; i++)  /* mark its upvalues */
      markobject(g, cl->l.upvals[i]);
  }
}