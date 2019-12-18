#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
struct TYPE_12__ {int Id; } ;
struct TYPE_11__ {int /*<<< orphan*/  Id; } ;
struct TYPE_13__ {int /*<<< orphan*/  adapter; scalar_t__ notifiedcall; int /*<<< orphan*/ * appl; scalar_t__ channels; int /*<<< orphan*/  State; scalar_t__ Id; TYPE_2__ Sig; int /*<<< orphan*/  tel; TYPE_1__ NL; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 int /*<<< orphan*/  CodecIdCheck (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  IDLE ; 
 scalar_t__ c_ind_mask_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  channel_flow_control_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  clear_b1_config (TYPE_3__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  listen_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncci_remove (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plci_free_msg_in_queue (TYPE_3__*) ; 

__attribute__((used)) static word plci_remove_check(PLCI   *plci)
{
  if(!plci) return true;
  if(!plci->NL.Id && c_ind_mask_empty (plci))
  {
    if(plci->Sig.Id == 0xff)
      plci->Sig.Id = 0;
    if(!plci->Sig.Id)
    {
      dbug(1,dprintf("plci_remove_complete(%x)",plci->Id));
      dbug(1,dprintf("tel=0x%x,Sig=0x%x",plci->tel,plci->Sig.Id));
      if (plci->Id)
      {
        CodecIdCheck(plci->adapter, plci);
        clear_b1_config (plci);
        ncci_remove (plci, 0, false);
        plci_free_msg_in_queue (plci);
        channel_flow_control_remove (plci);
        plci->Id = 0;
        plci->State = IDLE;
        plci->channels = 0;
        plci->appl = NULL;
        plci->notifiedcall = 0;
      }
      listen_check(plci->adapter);
      return true;
    }
  }
  return false;
}