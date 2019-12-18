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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_4__ {scalar_t__ env_counter; scalar_t__ ssctl; } ;
typedef  TYPE_1__ SlotState ;

/* Variables and functions */
 scalar_t__ SCSP_ENV_DECAY_END ; 
 int /*<<< orphan*/  ScspConvert32uto16s (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ScspGenerateAudioForSlot (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * scsp_bufL ; 
 int /*<<< orphan*/ * scsp_bufR ; 

__attribute__((used)) static u32 ScspSlotDebugAudio(SlotState *slot, s32 *workbuf, s16 *buf, u32 len)
{
   s32 *bufL, *bufR;

   bufL = workbuf;
   bufR = workbuf+len;
   scsp_bufL = bufL;
   scsp_bufR = bufR;

   if (slot->env_counter >= SCSP_ENV_DECAY_END)
      return 0;  // Not playing

   if (slot->ssctl)
      return 0; // not yet supported!

   memset(bufL, 0, sizeof(u32) * len);
   memset(bufR, 0, sizeof(u32) * len);
   ScspGenerateAudioForSlot(slot, len);
   ScspConvert32uto16s(bufL, bufR, buf, len);
   return len;
}