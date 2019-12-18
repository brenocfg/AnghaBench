#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16 ;
struct TYPE_4__ {scalar_t__ enabled; int status; int* addr; int* data; int* regs; void** old; } ;
struct TYPE_3__ {int rom; } ;

/* Variables and functions */
#define  AR_SWITCH_OFF 130 
#define  AR_SWITCH_ON 129 
#define  AR_SWITCH_TRAINER 128 
 scalar_t__ TYPE_AR ; 
 TYPE_2__ action_replay ; 
 TYPE_1__ cart ; 

void areplay_set_status(int status)
{
  if (action_replay.enabled)
  {
    /* no Trainer mode for normal Action Replay */
    if ((action_replay.enabled == TYPE_AR) && (status == AR_SWITCH_TRAINER))
    {
      status = AR_SWITCH_OFF;
    }

    /* check status changes */
    switch (status)
    {
      case AR_SWITCH_OFF:
      case AR_SWITCH_TRAINER:
      {
        /* check that patches were previously enabled */
        if (action_replay.status == AR_SWITCH_ON)
        {
          /* restore original data */
          *(uint16 *)(cart.rom + action_replay.addr[0]) = action_replay.old[0];
          *(uint16 *)(cart.rom + action_replay.addr[1]) = action_replay.old[1];
          *(uint16 *)(cart.rom + action_replay.addr[2]) = action_replay.old[2];
          *(uint16 *)(cart.rom + action_replay.addr[3]) = action_replay.old[3];
        }
        break;
      }

      case AR_SWITCH_ON:
      {
        /* check that patches were previously disabled */
        if (action_replay.status != AR_SWITCH_ON)
        {
          /* decode patch data */
          action_replay.data[0] = action_replay.regs[0];
          action_replay.data[1] = action_replay.regs[4];
          action_replay.data[2] = action_replay.regs[7];
          action_replay.data[3] = action_replay.regs[10];

          /* decode patch address ($000000-$7fffff) */
          action_replay.addr[0] = (action_replay.regs[1]  | ((action_replay.regs[2]   & 0x3f00) << 8)) << 1;
          action_replay.addr[1] = (action_replay.regs[5]  | ((action_replay.regs[6]   & 0x3f00) << 8)) << 1;
          action_replay.addr[2] = (action_replay.regs[8]  | ((action_replay.regs[9]   & 0x3f00) << 8)) << 1;
          action_replay.addr[3] = (action_replay.regs[11] | ((action_replay.regs[12]  & 0x3f00) << 8)) << 1;

          /* save original data */
          action_replay.old[0] = *(uint16 *)(cart.rom + action_replay.addr[0]);
          action_replay.old[1] = *(uint16 *)(cart.rom + action_replay.addr[1]);
          action_replay.old[2] = *(uint16 *)(cart.rom + action_replay.addr[2]);
          action_replay.old[3] = *(uint16 *)(cart.rom + action_replay.addr[3]);

          /* patch new data */
          *(uint16 *)(cart.rom + action_replay.addr[0]) = action_replay.data[0];
          *(uint16 *)(cart.rom + action_replay.addr[1]) = action_replay.data[1];
          *(uint16 *)(cart.rom + action_replay.addr[2]) = action_replay.data[2];
          *(uint16 *)(cart.rom + action_replay.addr[3]) = action_replay.data[3];
        }
        break;
      }

      default:
      {
        return;
      }
    }

    /* update status */
    action_replay.status = status;
  }
}