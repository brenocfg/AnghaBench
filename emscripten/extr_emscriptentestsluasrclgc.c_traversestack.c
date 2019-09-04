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
struct TYPE_6__ {int stacksize; int /*<<< orphan*/ * stack; int /*<<< orphan*/ * top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int lu_mem ;
struct TYPE_7__ {scalar_t__ gcstate; } ;
typedef  TYPE_2__ global_State ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/ * StkId ;

/* Variables and functions */
 scalar_t__ GCSatomic ; 
 int /*<<< orphan*/  markvalue (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnilvalue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static lu_mem traversestack (global_State *g, lua_State *th) {
  StkId o = th->stack;
  if (o == NULL)
    return 1;  /* stack not completely built yet */
  for (; o < th->top; o++)
    markvalue(g, o);
  if (g->gcstate == GCSatomic) {  /* final traversal? */
    StkId lim = th->stack + th->stacksize;  /* real end of stack */
    for (; o < lim; o++)  /* clear not-marked stack slice */
      setnilvalue(o);
  }
  return sizeof(lua_State) + sizeof(TValue) * th->stacksize;
}