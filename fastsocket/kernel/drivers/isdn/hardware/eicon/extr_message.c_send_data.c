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
typedef  size_t word ;
typedef  void* byte ;
struct TYPE_15__ {int XNum; size_t ReqCh; void* Req; int /*<<< orphan*/  Id; TYPE_1__* X; } ;
struct TYPE_14__ {int Length; int Flags; int /*<<< orphan*/  P; } ;
struct TYPE_13__ {size_t* ncci_next; size_t* ncci_ch; int* ch_flow_control; scalar_t__* ncci_state; int /*<<< orphan*/  (* request ) (TYPE_6__*) ;int /*<<< orphan*/  Id; TYPE_3__* ncci; } ;
struct TYPE_12__ {size_t data_out; TYPE_5__* DBuffer; scalar_t__ data_pending; } ;
struct TYPE_11__ {size_t ncci_ring_list; size_t send_disc; scalar_t__ B2_prot; scalar_t__ B3_prot; int data_sent; int /*<<< orphan*/  command; TYPE_6__ NL; void* nl_req; TYPE_1__* NData; int /*<<< orphan*/  data_sent_ptr; int /*<<< orphan*/  appl; TYPE_4__* adapter; } ;
struct TYPE_10__ {int PLength; void* P; } ;
typedef  TYPE_2__ PLCI ;
typedef  TYPE_3__ NCCI ;
typedef  TYPE_4__ DIVA_CAPI_ADAPTER ;
typedef  TYPE_5__ DATA_B3_DESC ;

/* Variables and functions */
 scalar_t__ B2_V120_ASYNC ; 
 scalar_t__ B2_V120_ASYNC_V42BIS ; 
 scalar_t__ B2_V120_BIT_TRANSPARENT ; 
 scalar_t__ B3_RTP ; 
 scalar_t__ CONNECTED ; 
 scalar_t__ INC_ACT_PENDING ; 
 scalar_t__ N_BDATA ; 
 int N_DATA ; 
 void* N_DISC ; 
 int N_OK_FC_PENDING ; 
 scalar_t__ N_UDATA ; 
 void* TransmitBufferGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _DISCONNECT_B3_R ; 
 int /*<<< orphan*/  cleanup_ncci_data (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 
 void* v120_break_header ; 
 void* v120_default_header ; 

__attribute__((used)) static void send_data(PLCI *plci)
{
  DIVA_CAPI_ADAPTER   * a;
  DATA_B3_DESC   * data;
  NCCI   *ncci_ptr;
  word ncci;

  if (!plci->nl_req && plci->ncci_ring_list)
  {
    a = plci->adapter;
    ncci = plci->ncci_ring_list;
    do
    {
      ncci = a->ncci_next[ncci];
      ncci_ptr = &(a->ncci[ncci]);
      if (!(a->ncci_ch[ncci]
         && (a->ch_flow_control[a->ncci_ch[ncci]] & N_OK_FC_PENDING)))
      {
        if (ncci_ptr->data_pending)
        {
          if ((a->ncci_state[ncci] == CONNECTED)
           || (a->ncci_state[ncci] == INC_ACT_PENDING)
           || (plci->send_disc == ncci))
          {
            data = &(ncci_ptr->DBuffer[ncci_ptr->data_out]);
            if ((plci->B2_prot == B2_V120_ASYNC)
             || (plci->B2_prot == B2_V120_ASYNC_V42BIS)
             || (plci->B2_prot == B2_V120_BIT_TRANSPARENT))
            {
              plci->NData[1].P = TransmitBufferGet (plci->appl, data->P);
              plci->NData[1].PLength = data->Length;
              if (data->Flags & 0x10)
                plci->NData[0].P = v120_break_header;
              else
                plci->NData[0].P = v120_default_header;
              plci->NData[0].PLength = 1 ;
              plci->NL.XNum = 2;
              plci->NL.Req = plci->nl_req = (byte)((data->Flags&0x07)<<4 |N_DATA);
            }
            else
            {
              plci->NData[0].P = TransmitBufferGet (plci->appl, data->P);
              plci->NData[0].PLength = data->Length;
              if (data->Flags & 0x10)
                plci->NL.Req = plci->nl_req = (byte)N_UDATA;

              else if ((plci->B3_prot == B3_RTP) && (data->Flags & 0x01))
                plci->NL.Req = plci->nl_req = (byte)N_BDATA;

              else
                plci->NL.Req = plci->nl_req = (byte)((data->Flags&0x07)<<4 |N_DATA);
            }
            plci->NL.X = plci->NData;
            plci->NL.ReqCh = a->ncci_ch[ncci];
            dbug(1,dprintf("%x:DREQ(%x:%x)",a->Id,plci->NL.Id,plci->NL.Req));
            plci->data_sent = true;
            plci->data_sent_ptr = data->P;
            a->request(&plci->NL);
          }
          else {
            cleanup_ncci_data (plci, ncci);
          }
        }
        else if (plci->send_disc == ncci)
        {
          /* dprintf("N_DISC"); */
          plci->NData[0].PLength = 0;
          plci->NL.ReqCh = a->ncci_ch[ncci];
          plci->NL.Req = plci->nl_req = N_DISC;
          a->request(&plci->NL);
          plci->command = _DISCONNECT_B3_R;
          plci->send_disc = 0;
        }
      }
    } while (!plci->nl_req && (ncci != plci->ncci_ring_list));
    plci->ncci_ring_list = ncci;
  }
}