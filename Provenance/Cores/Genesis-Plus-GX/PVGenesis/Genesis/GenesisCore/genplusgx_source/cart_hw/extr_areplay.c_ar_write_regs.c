#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_8__ {int* regs; scalar_t__ status; } ;
struct TYPE_7__ {int /*<<< orphan*/  rom; } ;
struct TYPE_6__ {TYPE_1__* memory_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ AR_SWITCH_OFF ; 
 scalar_t__ AR_SWITCH_ON ; 
 TYPE_4__ action_replay ; 
 int /*<<< orphan*/  areplay_set_status (scalar_t__) ; 
 TYPE_3__ cart ; 
 TYPE_2__ m68k ; 
 int /*<<< orphan*/  m68k_unused_16_w (int,int) ; 

__attribute__((used)) static void ar_write_regs(uint32 address, uint32 data)
{
  /* register offset */
  int offset = (address & 0xffff) >> 1;
  if (offset > 12)
  {
    m68k_unused_16_w(address,data);
    return;
  }

  /* update internal register */
  action_replay.regs[offset] = data;

  /* MODE register */
  if (action_replay.regs[3] == 0xffff)
  {
    /* check switch status */
    if (action_replay.status == AR_SWITCH_ON)
    {
      /* reset existing patches */
      areplay_set_status(AR_SWITCH_OFF);
      areplay_set_status(AR_SWITCH_ON);
    }

    /* enable Cartridge ROM */
    m68k.memory_map[0].base = cart.rom;
  }
}