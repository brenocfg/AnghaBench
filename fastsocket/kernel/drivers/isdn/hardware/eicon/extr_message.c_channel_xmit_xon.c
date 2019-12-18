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
typedef  scalar_t__ byte ;
struct TYPE_11__ {int XNum; TYPE_1__* X; scalar_t__ ReqCh; scalar_t__ Req; int /*<<< orphan*/  Id; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* request ) (TYPE_4__*) ;int /*<<< orphan*/ * ch_flow_control; } ;
struct TYPE_9__ {TYPE_4__ NL; TYPE_3__* adapter; TYPE_1__* NData; int /*<<< orphan*/ * RBuffer; scalar_t__ nl_req; scalar_t__ nl_remove_id; } ;
struct TYPE_8__ {scalar_t__ PLength; int /*<<< orphan*/ * P; } ;
typedef  TYPE_2__ PLCI ;
typedef  TYPE_3__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ N_XON ; 
 int /*<<< orphan*/  N_XON_REQ ; 
 int /*<<< orphan*/  N_XON_SENT ; 
 scalar_t__ find_channel_with_pending_x_on (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

__attribute__((used)) static void channel_xmit_xon (PLCI   * plci) {
  DIVA_CAPI_ADAPTER   * a = plci->adapter;
  byte ch;

  if (plci->nl_req || !plci->NL.Id || plci->nl_remove_id) {
    return;
  }
  if ((ch = (byte)find_channel_with_pending_x_on (a, plci)) == 0) {
    return;
  }
  a->ch_flow_control[ch] &= ~N_XON_REQ;
  a->ch_flow_control[ch] |= N_XON_SENT;

  plci->NL.Req = plci->nl_req = (byte)N_XON;
  plci->NL.ReqCh         = ch;
  plci->NL.X             = plci->NData;
  plci->NL.XNum          = 1;
  plci->NData[0].P       = &plci->RBuffer[0];
  plci->NData[0].PLength = 0;

  plci->adapter->request(&plci->NL);
}