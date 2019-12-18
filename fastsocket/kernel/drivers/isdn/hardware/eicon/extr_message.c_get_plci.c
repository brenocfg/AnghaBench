#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  scalar_t__ byte ;
struct TYPE_14__ {size_t max_plci; TYPE_3__* plci; } ;
struct TYPE_12__ {scalar_t__ Id; } ;
struct TYPE_11__ {scalar_t__ Id; } ;
struct TYPE_13__ {int data_sent; int manufacturer; int call_dir; int cr_enquiry; int ncpi_state; scalar_t__ Id; scalar_t__ vsprotdialect; scalar_t__ vsprot; scalar_t__ vswitchstate; scalar_t__ notifiedcall; scalar_t__ requested_options; scalar_t__ requested_options_conn; scalar_t__* ncpi_buffer; scalar_t__ nsf_control_bits; scalar_t__ fax_connect_info_length; scalar_t__* inc_dis_ncci_table; scalar_t__ ncci_ring_list; scalar_t__ hangup_flow_ctrl_timer; scalar_t__ ptyState; scalar_t__ spoofed_msg; scalar_t__ adv_nl; scalar_t__ nl_remove_id; scalar_t__ nl_global_req; scalar_t__ sig_remove_id; scalar_t__ sig_global_req; scalar_t__ send_disc; void* msg_in_wrap_pos; void* msg_in_read_pos; void* msg_in_write_pos; scalar_t__ req_out; scalar_t__ req_in; scalar_t__ req_in_start; scalar_t__ number; scalar_t__ m_command; scalar_t__ command; scalar_t__ B3_prot; scalar_t__ B2_prot; scalar_t__ B1_resource; scalar_t__ tel; scalar_t__ channels; void* SuppState; void* State; int /*<<< orphan*/ * relatedPTYPLCI; int /*<<< orphan*/ * appl; scalar_t__ nl_req; scalar_t__ sig_req; TYPE_2__ NL; TYPE_1__ Sig; } ;
typedef  TYPE_3__ PLCI ;
typedef  TYPE_4__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int CALL_DIR_ORIGINATE ; 
 int CALL_DIR_OUT ; 
 void* IDLE ; 
 size_t MAX_CHANNELS_PER_PLCI ; 
 void* MSG_IN_QUEUE_SIZE ; 
 int /*<<< orphan*/  clear_c_ind_mask (TYPE_3__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  dump_plcis (TYPE_4__*) ; 
 int /*<<< orphan*/  init_b1_config (TYPE_3__*) ; 
 int /*<<< orphan*/  init_internal_command_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  set_group_ind_mask (TYPE_3__*) ; 

__attribute__((used)) static word get_plci(DIVA_CAPI_ADAPTER *a)
{
  word i,j;
  PLCI   * plci;

  dump_plcis (a);
  for(i=0;i<a->max_plci && a->plci[i].Id;i++);
  if(i==a->max_plci) {
    dbug(1,dprintf("get_plci: out of PLCIs"));
    return 0;
  }
  plci = &a->plci[i];
  plci->Id = (byte)(i+1);

  plci->Sig.Id = 0;
  plci->NL.Id = 0;
  plci->sig_req = 0;
  plci->nl_req = 0;

  plci->appl = NULL;
  plci->relatedPTYPLCI = NULL;
  plci->State = IDLE;
  plci->SuppState = IDLE;
  plci->channels = 0;
  plci->tel = 0;
  plci->B1_resource = 0;
  plci->B2_prot = 0;
  plci->B3_prot = 0;

  plci->command = 0;
  plci->m_command = 0;
  init_internal_command_queue (plci);
  plci->number = 0;
  plci->req_in_start = 0;
  plci->req_in = 0;
  plci->req_out = 0;
  plci->msg_in_write_pos = MSG_IN_QUEUE_SIZE;
  plci->msg_in_read_pos = MSG_IN_QUEUE_SIZE;
  plci->msg_in_wrap_pos = MSG_IN_QUEUE_SIZE;

  plci->data_sent = false;
  plci->send_disc = 0;
  plci->sig_global_req = 0;
  plci->sig_remove_id = 0;
  plci->nl_global_req = 0;
  plci->nl_remove_id = 0;
  plci->adv_nl = 0;
  plci->manufacturer = false;
  plci->call_dir = CALL_DIR_OUT | CALL_DIR_ORIGINATE;
  plci->spoofed_msg = 0;
  plci->ptyState = 0;
  plci->cr_enquiry = false;
  plci->hangup_flow_ctrl_timer = 0;

  plci->ncci_ring_list = 0;
  for(j=0;j<MAX_CHANNELS_PER_PLCI;j++) plci->inc_dis_ncci_table[j] = 0;
  clear_c_ind_mask (plci);
  set_group_ind_mask (plci);
  plci->fax_connect_info_length = 0;
  plci->nsf_control_bits = 0;
  plci->ncpi_state = 0x00;
  plci->ncpi_buffer[0] = 0;

  plci->requested_options_conn = 0;
  plci->requested_options = 0;
  plci->notifiedcall = 0;
  plci->vswitchstate = 0;
  plci->vsprot = 0;
  plci->vsprotdialect = 0;
  init_b1_config (plci);
  dbug(1,dprintf("get_plci(%x)",plci->Id));
  return i+1;
}