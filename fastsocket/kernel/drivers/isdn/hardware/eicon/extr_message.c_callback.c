#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  size_t byte ;
struct TYPE_27__ {int length; size_t command; } ;
struct TYPE_25__ {scalar_t__ Data; } ;
struct TYPE_26__ {TYPE_2__ data_b3_req; } ;
struct TYPE_31__ {TYPE_4__ header; TYPE_3__ info; } ;
struct TYPE_30__ {scalar_t__* FlowControlIdTable; int* ch_flow_control; scalar_t__* ch_flow_plci; scalar_t__* FlowControlSkipTable; TYPE_5__* plci; } ;
struct TYPE_29__ {int* user; scalar_t__ Id; size_t Req; size_t Rc; int Ind; int complete; size_t RcCh; size_t ReqCh; size_t IndCh; int RNR; } ;
struct TYPE_24__ {int XNum; } ;
struct TYPE_28__ {scalar_t__ nl_remove_id; scalar_t__ rx_dma_descriptor; scalar_t__ Id; size_t nl_global_req; int data_sent; size_t sig_global_req; int msg_in_write_pos; int msg_in_read_pos; int msg_in_wrap_pos; int li_notify_update; scalar_t__ msg_in_queue; scalar_t__ internal_command; int /*<<< orphan*/  req_in; scalar_t__ sig_req; scalar_t__ sig_remove_id; TYPE_1__ NL; scalar_t__ nl_req; } ;
typedef  TYPE_5__ PLCI ;
typedef  TYPE_6__ ENTITY ;
typedef  TYPE_7__ DIVA_CAPI_ADAPTER ;
typedef  TYPE_8__ CAPI_MSG ;
typedef  int /*<<< orphan*/  APPL ;

/* Variables and functions */
 size_t ASSIGN_OK ; 
 int DIVA_CAPI_SUPPORTS_NO_CANCEL (TYPE_7__*) ; 
 void* MSG_IN_OVERHEAD ; 
 void* MSG_IN_QUEUE_SIZE ; 
 size_t N_DISC ; 
 size_t N_DISC_ACK ; 
 int N_OK_FC_PENDING ; 
 int N_RX_FLOW_CONTROL_MASK ; 
 size_t N_XON ; 
 size_t OK ; 
 size_t OK_FC ; 
 size_t REMOVE ; 
 int /*<<< orphan*/  TransmitBufferFree (int /*<<< orphan*/ *,size_t*) ; 
 size_t _DATA_B3_R ; 
 TYPE_7__* adapter ; 
 int api_put (int /*<<< orphan*/ *,TYPE_8__*) ; 
 int /*<<< orphan*/  channel_flow_control_remove (TYPE_5__*) ; 
 int /*<<< orphan*/  channel_x_on (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  channel_xmit_xon (TYPE_5__*) ; 
 int /*<<< orphan*/  control_rc (TYPE_5__*,size_t,size_t,size_t,size_t,int) ; 
 int /*<<< orphan*/  data_rc (TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diva_free_dma_descriptor (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  mixer_notify_update (TYPE_5__*,int) ; 
 int /*<<< orphan*/  nl_ind (TYPE_5__*) ; 
 int /*<<< orphan*/  send_data (TYPE_5__*) ; 
 int /*<<< orphan*/  send_req (TYPE_5__*) ; 
 int /*<<< orphan*/  sig_ind (TYPE_5__*) ; 

void   callback(ENTITY   * e)
{
  DIVA_CAPI_ADAPTER   * a;
  APPL   * appl;
  PLCI   * plci;
  CAPI_MSG   *m;
  word i, j;
  byte rc;
  byte ch;
  byte req;
  byte global_req;
  int no_cancel_rc;

  dbug(1,dprintf("%x:CB(%x:Req=%x,Rc=%x,Ind=%x)",
                 (e->user[0]+1)&0x7fff,e->Id,e->Req,e->Rc,e->Ind));

  a = &(adapter[(byte)e->user[0]]);
  plci = &(a->plci[e->user[1]]);
  no_cancel_rc = DIVA_CAPI_SUPPORTS_NO_CANCEL(a);

  /*
     If new protocol code and new XDI is used then CAPI should work
     fully in accordance with IDI cpec an look on callback field instead
     of Rc field for return codes.
   */
  if (((e->complete == 0xff) && no_cancel_rc) ||
      (e->Rc && !no_cancel_rc)) {
    rc = e->Rc;
    ch = e->RcCh;
    req = e->Req;
    e->Rc = 0;

    if (e->user[0] & 0x8000)
    {
      /*
         If REMOVE request was sent then we have to wait until
         return code with Id set to zero arrives.
         All other return codes should be ignored.
         */
      if (req == REMOVE)
      {
        if (e->Id)
        {
          dbug(1,dprintf("cancel RC in REMOVE state"));
          return;
        }
        channel_flow_control_remove (plci);
        for (i = 0; i < 256; i++)
        {
          if (a->FlowControlIdTable[i] == plci->nl_remove_id)
            a->FlowControlIdTable[i] = 0;
        }
        plci->nl_remove_id = 0;
        if (plci->rx_dma_descriptor > 0) {
          diva_free_dma_descriptor (plci, plci->rx_dma_descriptor - 1);
          plci->rx_dma_descriptor = 0;
        }
      }
      if (rc == OK_FC)
      {
        a->FlowControlIdTable[ch] = e->Id;
        a->FlowControlSkipTable[ch] = 0;

        a->ch_flow_control[ch] |= N_OK_FC_PENDING;
        a->ch_flow_plci[ch] = plci->Id;
        plci->nl_req = 0;
      }
      else
      {
        /*
          Cancel return codes self, if feature was requested
          */
        if (no_cancel_rc && (a->FlowControlIdTable[ch] == e->Id) && e->Id) {
          a->FlowControlIdTable[ch] = 0;
          if ((rc == OK) && a->FlowControlSkipTable[ch]) {
            dbug(3,dprintf ("XDI CAPI: RC cancelled Id:0x02, Ch:%02x",                              e->Id, ch));
            return;
          }
        }

        if (a->ch_flow_control[ch] & N_OK_FC_PENDING)
        {
          a->ch_flow_control[ch] &= ~N_OK_FC_PENDING;
          if (ch == e->ReqCh)
            plci->nl_req = 0;
        }
        else
          plci->nl_req = 0;
      }
      if (plci->nl_req)
        control_rc (plci, 0, rc, ch, 0, true);
      else
      {
        if (req == N_XON)
        {
          channel_x_on (plci, ch);
          if (plci->internal_command)
            control_rc (plci, req, rc, ch, 0, true);
        }
        else
        {
          if (plci->nl_global_req)
          {
            global_req = plci->nl_global_req;
            plci->nl_global_req = 0;
            if (rc != ASSIGN_OK) {
              e->Id = 0;
              if (plci->rx_dma_descriptor > 0) {
                diva_free_dma_descriptor (plci, plci->rx_dma_descriptor - 1);
                plci->rx_dma_descriptor = 0;
              }
            }
            channel_xmit_xon (plci);
            control_rc (plci, 0, rc, ch, global_req, true);
          }
          else if (plci->data_sent)
          {
            channel_xmit_xon (plci);
            plci->data_sent = false;
            plci->NL.XNum = 1;
            data_rc (plci, ch);
            if (plci->internal_command)
              control_rc (plci, req, rc, ch, 0, true);
          }
          else
          {
            channel_xmit_xon (plci);
            control_rc (plci, req, rc, ch, 0, true);
          }
        }
      }
    }
    else
    {
      /*
         If REMOVE request was sent then we have to wait until
         return code with Id set to zero arrives.
         All other return codes should be ignored.
         */
      if (req == REMOVE)
      {
        if (e->Id)
        {
          dbug(1,dprintf("cancel RC in REMOVE state"));
          return;
        }
        plci->sig_remove_id = 0;
      }
      plci->sig_req = 0;
      if (plci->sig_global_req)
      {
        global_req = plci->sig_global_req;
        plci->sig_global_req = 0;
        if (rc != ASSIGN_OK)
          e->Id = 0;
        channel_xmit_xon (plci);
        control_rc (plci, 0, rc, ch, global_req, false);
      }
      else
      {
        channel_xmit_xon (plci);
        control_rc (plci, req, rc, ch, 0, false);
      }
    }
    /*
      Again: in accordance with IDI spec Rc and Ind can't be delivered in the
      same callback. Also if new XDI and protocol code used then jump
      direct to finish.
      */
    if (no_cancel_rc) {
      channel_xmit_xon(plci);
      goto capi_callback_suffix;
    }
  }

  channel_xmit_xon(plci);

  if (e->Ind) {
    if (e->user[0] &0x8000) {
      byte Ind = e->Ind & 0x0f;
      byte Ch = e->IndCh;
      if (((Ind==N_DISC) || (Ind==N_DISC_ACK)) &&
          (a->ch_flow_plci[Ch] == plci->Id)) {
        if (a->ch_flow_control[Ch] & N_RX_FLOW_CONTROL_MASK) {
          dbug(3,dprintf ("XDI CAPI: I: pending N-XON Ch:%02x", Ch));
        }
        a->ch_flow_control[Ch] &= ~N_RX_FLOW_CONTROL_MASK;
      }
      nl_ind(plci);
      if ((e->RNR != 1) &&
          (a->ch_flow_plci[Ch] == plci->Id) &&
          (a->ch_flow_control[Ch] & N_RX_FLOW_CONTROL_MASK)) {
        a->ch_flow_control[Ch] &= ~N_RX_FLOW_CONTROL_MASK;
        dbug(3,dprintf ("XDI CAPI: I: remove faked N-XON Ch:%02x", Ch));
      }
    } else {
      sig_ind(plci);
    }
    e->Ind = 0;
  }

capi_callback_suffix:

  while (!plci->req_in
   && !plci->internal_command
   && (plci->msg_in_write_pos != plci->msg_in_read_pos))
  {
    j = (plci->msg_in_read_pos == plci->msg_in_wrap_pos) ? 0 : plci->msg_in_read_pos;

    i = (((CAPI_MSG   *)(&((byte   *)(plci->msg_in_queue))[j]))->header.length + 3) & 0xfffc;

    m = (CAPI_MSG   *)(&((byte   *)(plci->msg_in_queue))[j]);
    appl = *((APPL   *   *)(&((byte   *)(plci->msg_in_queue))[j+i]));
    dbug(1,dprintf("dequeue msg(0x%04x) - write=%d read=%d wrap=%d",
      m->header.command, plci->msg_in_write_pos, plci->msg_in_read_pos, plci->msg_in_wrap_pos));
    if (plci->msg_in_read_pos == plci->msg_in_wrap_pos)
    {
      plci->msg_in_wrap_pos = MSG_IN_QUEUE_SIZE;
      plci->msg_in_read_pos = i + MSG_IN_OVERHEAD;
    }
    else
    {
      plci->msg_in_read_pos = j + i + MSG_IN_OVERHEAD;
    }
    if (plci->msg_in_read_pos == plci->msg_in_write_pos)
    {
      plci->msg_in_write_pos = MSG_IN_QUEUE_SIZE;
      plci->msg_in_read_pos = MSG_IN_QUEUE_SIZE;
    }
    else if (plci->msg_in_read_pos == plci->msg_in_wrap_pos)
    {
      plci->msg_in_read_pos = MSG_IN_QUEUE_SIZE;
      plci->msg_in_wrap_pos = MSG_IN_QUEUE_SIZE;
    }
    i = api_put (appl, m);
    if (i != 0)
    {
      if (m->header.command == _DATA_B3_R)

        TransmitBufferFree (appl, (byte *)(long)(m->info.data_b3_req.Data));

      dbug(1,dprintf("Error 0x%04x from msg(0x%04x)", i, m->header.command));
      break;
    }

    if (plci->li_notify_update)
    {
      plci->li_notify_update = false;
      mixer_notify_update (plci, false);
    }

  }
  send_data(plci);
  send_req(plci);
}