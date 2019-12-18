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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ manualchange; } ;
struct TYPE_3__ {int FBCR; } ;

/* Variables and functions */
 TYPE_2__ Vdp1External ; 
 TYPE_1__* Vdp1Regs ; 
 int /*<<< orphan*/  VidsoftWaitForVdp1Thread () ; 
 int /*<<< orphan*/ * vdp1backframebuffer ; 
 int /*<<< orphan*/ * vdp1frontframebuffer ; 
 scalar_t__ vidsoft_vdp1_thread_enabled ; 

void VIDSoftVdp1SwapFrameBuffer(void)
{
   if (((Vdp1Regs->FBCR & 2) == 0) || Vdp1External.manualchange)
   {
		u8 *temp;
      if (vidsoft_vdp1_thread_enabled)
      {
         VidsoftWaitForVdp1Thread();
      }

      temp = vdp1frontframebuffer;
      vdp1frontframebuffer = vdp1backframebuffer;
      vdp1backframebuffer = temp;
      Vdp1External.manualchange = 0;
   }
}