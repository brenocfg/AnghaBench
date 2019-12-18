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
typedef  int /*<<< orphan*/  Vdp1 ;
struct TYPE_2__ {int need_draw; scalar_t__ draw_finished; int /*<<< orphan*/ * back_framebuffer; int /*<<< orphan*/  regs; int /*<<< orphan*/ * ram; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDSoftVdp1DrawStartBody (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Vdp1DrawCommands (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Vdp1FakeDrawCommands (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Vdp1Ram ; 
 int /*<<< orphan*/ * Vdp1Regs ; 
 int /*<<< orphan*/  VidsoftWaitForVdp1Thread () ; 
 int /*<<< orphan*/  YAB_THREAD_VIDSOFT_VDP1 ; 
 int /*<<< orphan*/  YabThreadWake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vdp1backframebuffer ; 
 TYPE_1__ vidsoft_vdp1_thread_context ; 
 scalar_t__ vidsoft_vdp1_thread_enabled ; 

void VIDSoftVdp1DrawStart()
{
   if (vidsoft_vdp1_thread_enabled)
   {
      VidsoftWaitForVdp1Thread();

      //take a snapshot of the vdp1 state, to be used by the thread
      memcpy(vidsoft_vdp1_thread_context.ram, Vdp1Ram, 0x80000);
      memcpy(&vidsoft_vdp1_thread_context.regs, Vdp1Regs, sizeof(Vdp1));
      memcpy(vidsoft_vdp1_thread_context.back_framebuffer, vdp1backframebuffer, 0x40000);

      VIDSoftVdp1DrawStartBody(&vidsoft_vdp1_thread_context.regs, vidsoft_vdp1_thread_context.back_framebuffer);

      //start thread
      vidsoft_vdp1_thread_context.draw_finished = 0;
      vidsoft_vdp1_thread_context.need_draw = 1;
      YabThreadWake(YAB_THREAD_VIDSOFT_VDP1);

      Vdp1FakeDrawCommands(Vdp1Ram, Vdp1Regs);
   }
   else
   {
      VIDSoftVdp1DrawStartBody(Vdp1Regs, vdp1backframebuffer);
      Vdp1DrawCommands(Vdp1Ram, Vdp1Regs, vdp1backframebuffer);
   }
}