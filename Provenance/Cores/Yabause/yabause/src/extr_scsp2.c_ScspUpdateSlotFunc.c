#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ lfo_fm_shift; scalar_t__ lfo_am_shift; scalar_t__ pcm8b; int outshift_l; int outshift_r; void* audiogen; scalar_t__ ssctl; } ;
typedef  TYPE_1__ SlotState ;

/* Variables and functions */
 void****** scsp_audiogen_func_table ; 

__attribute__((used)) static void ScspUpdateSlotFunc(SlotState *slot)
{
   if (slot->ssctl)
      // FIXME: noise (ssctl==1) not implemented
      slot->audiogen = scsp_audiogen_func_table[0][0][0][0][0];
   else
      slot->audiogen = scsp_audiogen_func_table[slot->lfo_fm_shift >= 0]
                                               [slot->lfo_am_shift >= 0]
                                               [slot->pcm8b == 0]
                                               [slot->outshift_l != 31]
                                               [slot->outshift_r != 31];
}