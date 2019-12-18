#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_7__ {struct IsdnCardState* hardware; } ;
struct PStack {TYPE_1__ l1; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* statcallb ) (TYPE_5__*) ;} ;
struct IsdnCardState {TYPE_4__ iif; int /*<<< orphan*/  myid; } ;
struct TYPE_8__ {int hl_id; int proc; int /*<<< orphan*/ * data; int /*<<< orphan*/  datalen; scalar_t__ timeout; scalar_t__ ll_id; } ;
struct TYPE_9__ {TYPE_2__ dss1_io; } ;
struct TYPE_11__ {TYPE_3__ parm; int /*<<< orphan*/  arg; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_5__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  DSS1_STAT_INVOKE_BRD ; 
 int /*<<< orphan*/  ISDN_STAT_PROT ; 
 int /*<<< orphan*/  l3_debug (struct PStack*,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static void 
l3dss1_dummy_invoke(struct PStack *st, int cr, int id, 
                    int ident, u_char *p, u_char nlen)
{ isdn_ctrl ic;
  struct IsdnCardState *cs;
  
  l3_debug(st, "dummy invoke %s id=0x%x ident=0x%x datalen=%d",
               (cr == -1) ? "local" : "broadcast",id,ident,nlen);
  if (cr >= -1) return; /* ignore local data */

  cs = st->l1.hardware;
  ic.driver = cs->myid;
  ic.command = ISDN_STAT_PROT;
  ic.arg = DSS1_STAT_INVOKE_BRD;
  ic.parm.dss1_io.hl_id = id;
  ic.parm.dss1_io.ll_id = 0;
  ic.parm.dss1_io.proc = ident;
  ic.parm.dss1_io.timeout= 0;
  ic.parm.dss1_io.datalen = nlen;
  ic.parm.dss1_io.data = p;

  cs->iif.statcallb(&ic);
}