#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int lu_mem ;
struct TYPE_11__ {int size; } ;
struct TYPE_12__ {int gcstate; int GCmemtrav; int /*<<< orphan*/  gckind; int /*<<< orphan*/  tobefnz; int /*<<< orphan*/  mainthread; int /*<<< orphan*/  finobj; int /*<<< orphan*/  GCestimate; int /*<<< orphan*/ * gray; TYPE_1__ strt; } ;
typedef  TYPE_2__ global_State ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_2__* G (int /*<<< orphan*/ *) ; 
 int GCFINALIZECOST ; 
#define  GCSatomic 135 
#define  GCScallfin 134 
#define  GCSpause 133 
#define  GCSpropagate 132 
#define  GCSswpallgc 131 
#define  GCSswpend 130 
#define  GCSswpfinobj 129 
#define  GCSswptobefnz 128 
 int /*<<< orphan*/  KGC_EMERGENCY ; 
 int atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  checkSizes (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  entersweep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettotalbytes (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makewhite (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagateall (TYPE_2__*) ; 
 int /*<<< orphan*/  propagatemark (TYPE_2__*) ; 
 int /*<<< orphan*/  restartcollection (TYPE_2__*) ; 
 int runafewfinalizers (int /*<<< orphan*/ *) ; 
 int sweepstep (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lu_mem singlestep (lua_State *L) {
  global_State *g = G(L);
  switch (g->gcstate) {
    case GCSpause: {
      g->GCmemtrav = g->strt.size * sizeof(GCObject*);
      restartcollection(g);
      g->gcstate = GCSpropagate;
      return g->GCmemtrav;
    }
    case GCSpropagate: {
      g->GCmemtrav = 0;
      lua_assert(g->gray);
      propagatemark(g);
       if (g->gray == NULL)  /* no more gray objects? */
        g->gcstate = GCSatomic;  /* finish propagate phase */
      return g->GCmemtrav;  /* memory traversed in this step */
    }
    case GCSatomic: {
      lu_mem work;
      propagateall(g);  /* make sure gray list is empty */
      work = atomic(L);  /* work is what was traversed by 'atomic' */
      entersweep(L);
      g->GCestimate = gettotalbytes(g);  /* first estimate */;
      return work;
    }
    case GCSswpallgc: {  /* sweep "regular" objects */
      return sweepstep(L, g, GCSswpfinobj, &g->finobj);
    }
    case GCSswpfinobj: {  /* sweep objects with finalizers */
      return sweepstep(L, g, GCSswptobefnz, &g->tobefnz);
    }
    case GCSswptobefnz: {  /* sweep objects to be finalized */
      return sweepstep(L, g, GCSswpend, NULL);
    }
    case GCSswpend: {  /* finish sweeps */
      makewhite(g, g->mainthread);  /* sweep main thread */
      checkSizes(L, g);
      g->gcstate = GCScallfin;
      return 0;
    }
    case GCScallfin: {  /* call remaining finalizers */
      if (g->tobefnz && g->gckind != KGC_EMERGENCY) {
        int n = runafewfinalizers(L);
        return (n * GCFINALIZECOST);
      }
      else {  /* emergency mode or no more finalizers */
        g->gcstate = GCSpause;  /* finish collection */
        return 0;
      }
    }
    default: lua_assert(0); return 0;
  }
}