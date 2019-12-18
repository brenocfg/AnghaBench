#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ env_counter; int /*<<< orphan*/  (* audiogen ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ SlotState ;

/* Variables and functions */
 scalar_t__ SCSP_ENV_DECAY_END ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ScspGenerateAudioForSlot(SlotState *slot, u32 samples)
{
   if (slot->env_counter >= SCSP_ENV_DECAY_END)
      return;  // No sound is currently playing

   (*slot->audiogen)(slot, samples);
}