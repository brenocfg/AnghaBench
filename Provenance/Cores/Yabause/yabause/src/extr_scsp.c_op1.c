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
typedef  int u32 ;
struct TYPE_5__ {int attenuation; int lfo_counter; int lfo_pos; int waveform_phase_value; } ;
struct TYPE_4__ {int oct; int fns; size_t lfof; int plfows; int plfos; } ;
struct Slot {TYPE_2__ state; TYPE_1__ regs; } ;
struct TYPE_6__ {int* saw_table; int* square_table; int* tri_table; int* noise_table; } ;

/* Variables and functions */
 int* lfo_step_table ; 
 TYPE_3__ plfo ; 

void op1(struct Slot * slot)
{
   u32 oct = slot->regs.oct ^ 8;
   u32 fns = slot->regs.fns ^ 0x400;
   u32 phase_increment = fns << oct;
   int plfo_val = 0;
   int plfo_shifted = 0;

   if (slot->state.attenuation > 0x3bf)
      return;

   if (slot->state.lfo_counter % lfo_step_table[slot->regs.lfof] == 0)
   {
      slot->state.lfo_counter = 0;
      slot->state.lfo_pos++;

      if (slot->state.lfo_pos > 0xff)
         slot->state.lfo_pos = 0;
   }

   if (slot->regs.plfows == 0)
      plfo_val = plfo.saw_table[slot->state.lfo_pos];
   else if (slot->regs.plfows == 1)
      plfo_val = plfo.square_table[slot->state.lfo_pos];
   else if (slot->regs.plfows == 2)
      plfo_val = plfo.tri_table[slot->state.lfo_pos];
   else if (slot->regs.plfows == 3)
      plfo_val = plfo.noise_table[slot->state.lfo_pos];

   plfo_shifted = (plfo_val << slot->regs.plfos) >> 2;

   slot->state.waveform_phase_value &= (1 << 18) - 1;//18 fractional bits
   slot->state.waveform_phase_value += (phase_increment + plfo_shifted);
}