#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ word ;
struct TYPE_11__ {int Req; int ReqCh; int Id; TYPE_1__* X; } ;
struct TYPE_10__ {size_t req_in; size_t req_out; int nl_req; int sig_req; int* RBuffer; int nl_global_req; int sig_global_req; TYPE_2__* adapter; TYPE_1__* XData; TYPE_4__ Sig; TYPE_4__ NL; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* request ) (TYPE_4__*) ;int /*<<< orphan*/  Id; scalar_t__ adapter_disabled; } ;
struct TYPE_8__ {int* P; scalar_t__ PLength; } ;
typedef  TYPE_3__ PLCI ;
typedef  TYPE_4__ ENTITY ;

/* Variables and functions */
 int CAI ; 
 scalar_t__ GET_WORD (int*) ; 
 int NL_ID ; 
 int /*<<< orphan*/  channel_xmit_xon (TYPE_3__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void send_req(PLCI *plci)
{
  ENTITY   * e;
  word l;
/*  word i; */

  if(!plci) return;
  if(plci->adapter->adapter_disabled) return;
  channel_xmit_xon (plci);

        /* if nothing to do, return */
  if(plci->req_in==plci->req_out) return;
  dbug(1,dprintf("send_req(in=%d,out=%d)",plci->req_in,plci->req_out));

  if(plci->nl_req || plci->sig_req) return;

  l = GET_WORD(&plci->RBuffer[plci->req_out]);
  plci->req_out += 2;
  plci->XData[0].P = &plci->RBuffer[plci->req_out];
  plci->req_out += l;
  if(plci->RBuffer[plci->req_out]==1)
  {
    e = &plci->NL;
    plci->req_out++;
    e->Req = plci->nl_req = plci->RBuffer[plci->req_out++];
    e->ReqCh = plci->RBuffer[plci->req_out++];
    if(!(e->Id & 0x1f))
    {
      e->Id = NL_ID;
      plci->RBuffer[plci->req_out-4] = CAI;
      plci->RBuffer[plci->req_out-3] = 1;
      plci->RBuffer[plci->req_out-2] = (plci->Sig.Id==0xff) ? 0 : plci->Sig.Id;
      plci->RBuffer[plci->req_out-1] = 0;
      l+=3;
      plci->nl_global_req = plci->nl_req;
    }
    dbug(1,dprintf("%x:NLREQ(%x:%x:%x)",plci->adapter->Id,e->Id,e->Req,e->ReqCh));
  }
  else
  {
    e = &plci->Sig;
    if(plci->RBuffer[plci->req_out])
      e->Id = plci->RBuffer[plci->req_out];
    plci->req_out++;
    e->Req = plci->sig_req = plci->RBuffer[plci->req_out++];
    e->ReqCh = plci->RBuffer[plci->req_out++];
    if(!(e->Id & 0x1f))
      plci->sig_global_req = plci->sig_req;
    dbug(1,dprintf("%x:SIGREQ(%x:%x:%x)",plci->adapter->Id,e->Id,e->Req,e->ReqCh));
  }
  plci->XData[0].PLength = l;
  e->X = plci->XData;
  plci->adapter->request(e);
  dbug(1,dprintf("send_ok"));
}