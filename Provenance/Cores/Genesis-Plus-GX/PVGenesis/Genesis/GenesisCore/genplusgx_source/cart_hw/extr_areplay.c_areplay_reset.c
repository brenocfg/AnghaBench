#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  ram; int /*<<< orphan*/  rom; int /*<<< orphan*/  addr; int /*<<< orphan*/  data; int /*<<< orphan*/  old; int /*<<< orphan*/  regs; scalar_t__ enabled; } ;
struct TYPE_5__ {TYPE_1__* memory_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ AR_SWITCH_TRAINER ; 
 TYPE_3__ action_replay ; 
 TYPE_2__ m68k ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

void areplay_reset(int hard)
{
  if (action_replay.enabled)
  {
    if (hard || (action_replay.status == AR_SWITCH_TRAINER))
    {
      /* reset internal registers */
      memset(action_replay.regs, 0, sizeof(action_replay.regs));
      memset(action_replay.old, 0, sizeof(action_replay.old));
      memset(action_replay.data, 0, sizeof(action_replay.data));
      memset(action_replay.addr, 0, sizeof(action_replay.addr));

      /* by default, internal ROM is mapped at $000000-$00FFFF */
      m68k.memory_map[0].base = action_replay.rom;

      /* reset internal RAM on power-on */
      if (hard)
      {
        memset(action_replay.ram,0xff,0x10000);
      }
    }
  }
}