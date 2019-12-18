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
struct TYPE_5__ {int attenuation; size_t lfo_pos; scalar_t__ output; } ;
struct TYPE_4__ {int alfows; int alfos; int /*<<< orphan*/  tl; } ;
struct Slot {TYPE_2__ state; TYPE_1__ regs; } ;
typedef  scalar_t__ s16 ;
struct TYPE_6__ {int* saw_table; int* square_table; int* tri_table; int* noise_table; } ;

/* Variables and functions */
 TYPE_3__ alfo ; 
 scalar_t__ apply_volume (int /*<<< orphan*/ ,int,scalar_t__) ; 

void op5(struct Slot * slot)
{
   if (slot->state.attenuation > 0x3bf)
   {
      slot->state.output = 0;
      return;
   }
   else
   {
      int alfo_val = 0;
      int lfo_add = 0;
      s16 sample = 0;

      if (slot->regs.alfows == 0)
         alfo_val = alfo.saw_table[slot->state.lfo_pos];
      else if (slot->regs.alfows == 1)
         alfo_val = alfo.square_table[slot->state.lfo_pos];
      else if (slot->regs.alfows == 2)
         alfo_val = alfo.tri_table[slot->state.lfo_pos];
      else if (slot->regs.alfows == 3)
         alfo_val = alfo.noise_table[slot->state.lfo_pos];

      lfo_add = (((alfo_val + 1)) >> (7 - slot->regs.alfos)) << 1;

      sample = apply_volume(slot->regs.tl, slot->state.attenuation + lfo_add, slot->state.output);
      slot->state.output = sample;
   }
}