#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_13__ {scalar_t__ invoke_id; int /*<<< orphan*/  proc; int /*<<< orphan*/  ll_id; } ;
struct TYPE_14__ {TYPE_4__ ni1; } ;
struct l3_process {TYPE_5__ prot; TYPE_9__* st; int /*<<< orphan*/  timer; } ;
struct PStack {int dummy; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* statcallb ) (TYPE_7__*) ;} ;
struct IsdnCardState {TYPE_6__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_11__ {int /*<<< orphan*/ * data; scalar_t__ datalen; int /*<<< orphan*/  timeout; int /*<<< orphan*/  proc; int /*<<< orphan*/  ll_id; scalar_t__ hl_id; } ;
struct TYPE_12__ {TYPE_2__ ni1_io; } ;
struct TYPE_16__ {TYPE_3__ parm; int /*<<< orphan*/  arg; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_7__ isdn_ctrl ;
struct TYPE_10__ {struct IsdnCardState* hardware; } ;
struct TYPE_17__ {TYPE_1__ l1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_PROT ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NI1_STAT_INVOKE_ERR ; 
 int /*<<< orphan*/  free_invoke_id (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  l3_debug (struct PStack*,char*,int,int /*<<< orphan*/ ) ; 
 struct l3_process* l3ni1_search_dummy_proc (struct PStack*,int) ; 
 int /*<<< orphan*/  ni1_release_l3_process (struct l3_process*) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 

__attribute__((used)) static void 
l3ni1_dummy_error_return(struct PStack *st, int id, ulong error)
{ isdn_ctrl ic;
  struct IsdnCardState *cs;
  struct l3_process *pc = NULL; 

  if ((pc = l3ni1_search_dummy_proc(st, id)))
   { L3DelTimer(&pc->timer); /* remove timer */

     cs = pc->st->l1.hardware;
     ic.driver = cs->myid;
     ic.command = ISDN_STAT_PROT;
     ic.arg = NI1_STAT_INVOKE_ERR;
     ic.parm.ni1_io.hl_id = pc->prot.ni1.invoke_id;
     ic.parm.ni1_io.ll_id = pc->prot.ni1.ll_id;
     ic.parm.ni1_io.proc = pc->prot.ni1.proc;
     ic.parm.ni1_io.timeout= error;
     ic.parm.ni1_io.datalen = 0;
     ic.parm.ni1_io.data = NULL;
     free_invoke_id(pc->st, pc->prot.ni1.invoke_id);
     pc->prot.ni1.invoke_id = 0; /* reset id */

     cs->iif.statcallb(&ic);
     ni1_release_l3_process(pc); 
   }
  else
   l3_debug(st, "dummy return error id=0x%x error=0x%lx",id,error);
}