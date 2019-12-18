#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* draw_finished; int /*<<< orphan*/  color_ram; int /*<<< orphan*/  lines; int /*<<< orphan*/  ram; int /*<<< orphan*/  regs; scalar_t__* need_draw; } ;

/* Variables and functions */
 size_t TITAN_SPRITE ; 
 int /*<<< orphan*/  Vdp1Regs ; 
 int /*<<< orphan*/  VidsoftDrawSprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YabThreadSleep () ; 
 int /*<<< orphan*/  sprite_window_mask ; 
 int /*<<< orphan*/  vdp1frontframebuffer ; 
 TYPE_1__ vidsoft_thread_context ; 

void VidsoftSpriteThread(void * data)
{
   for (;;)
   {
      if (vidsoft_thread_context.need_draw[TITAN_SPRITE])
      {
         vidsoft_thread_context.need_draw[TITAN_SPRITE] = 0;
         VidsoftDrawSprite(&vidsoft_thread_context.regs, sprite_window_mask, vdp1frontframebuffer, vidsoft_thread_context.ram, Vdp1Regs,vidsoft_thread_context.lines, vidsoft_thread_context.color_ram);
         vidsoft_thread_context.draw_finished[TITAN_SPRITE] = 1;
      }
      YabThreadSleep();
   }
}