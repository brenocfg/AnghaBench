#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int idx; scalar_t__ instack; } ;
typedef  TYPE_3__ Upvaldesc ;
struct TYPE_13__ {int /*<<< orphan*/ * v; } ;
typedef  TYPE_4__ UpVal ;
struct TYPE_11__ {TYPE_1__** upvals; } ;
struct TYPE_15__ {TYPE_2__ l; } ;
struct TYPE_14__ {int sizeupvalues; TYPE_3__* upvalues; TYPE_6__* cache; } ;
struct TYPE_10__ {int /*<<< orphan*/ * v; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/ * StkId ;
typedef  TYPE_5__ Proto ;
typedef  TYPE_6__ Closure ;

/* Variables and functions */

__attribute__((used)) static Closure *getcached (Proto *p, UpVal **encup, StkId base) {
  Closure *c = p->cache;
  if (c != NULL) {  /* is there a cached closure? */
    int nup = p->sizeupvalues;
    Upvaldesc *uv = p->upvalues;
    int i;
    for (i = 0; i < nup; i++) {  /* check whether it has right upvalues */
      TValue *v = uv[i].instack ? base + uv[i].idx : encup[uv[i].idx]->v;
      if (c->l.upvals[i]->v != v)
        return NULL;  /* wrong upvalue; cannot reuse closure */
    }
  }
  return c;  /* return cached closure (or NULL if no cached closure) */
}