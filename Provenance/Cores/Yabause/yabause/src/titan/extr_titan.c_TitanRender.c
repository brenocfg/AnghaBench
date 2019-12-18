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
typedef  int /*<<< orphan*/  pixel_t ;
struct TYPE_4__ {int CCCTL; int SFPRMD; int LNCLEN; int SDCTL; int PRINA; int PRINB; int PRIR; } ;
struct TYPE_3__ {int* layer_priority; int /*<<< orphan*/  vdp2height; int /*<<< orphan*/  trans; int /*<<< orphan*/  inited; } ;

/* Variables and functions */
 size_t TITAN_NBG0 ; 
 size_t TITAN_NBG1 ; 
 size_t TITAN_NBG2 ; 
 size_t TITAN_NBG3 ; 
 size_t TITAN_RBG0 ; 
 int /*<<< orphan*/  TitanRenderSimplifiedCheck (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TitanRenderThreads (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* Vdp2Regs ; 
 TYPE_1__ tt_context ; 
 scalar_t__ vidsoft_num_priority_threads ; 

void TitanRender(pixel_t * dispbuffer)
{
   int can_use_simplified_rendering = 1;

   if (!tt_context.inited || (!tt_context.trans))
   {
      return;
   }

   //using color calculation
   if ((Vdp2Regs->CCCTL & 0x807f) != 0)
      can_use_simplified_rendering = 0;

   //using special priority
   if ((Vdp2Regs->SFPRMD & 0x3ff) != 0)
      can_use_simplified_rendering = 0;

   //using line screen
   if ((Vdp2Regs->LNCLEN & 0x1f) != 0)
      can_use_simplified_rendering = 0;

   //using shadow
   if ((Vdp2Regs->SDCTL & 0x13F) != 0)
      can_use_simplified_rendering = 0;

   tt_context.layer_priority[TITAN_NBG0] = Vdp2Regs->PRINA & 0x7;
   tt_context.layer_priority[TITAN_NBG1] = ((Vdp2Regs->PRINA >> 8) & 0x7);
   tt_context.layer_priority[TITAN_NBG2] = (Vdp2Regs->PRINB & 0x7);
   tt_context.layer_priority[TITAN_NBG3] = ((Vdp2Regs->PRINB >> 8) & 0x7);
   tt_context.layer_priority[TITAN_RBG0] = (Vdp2Regs->PRIR & 0x7);

   if (vidsoft_num_priority_threads > 0)
   {
      TitanRenderThreads(dispbuffer, can_use_simplified_rendering);
   }
   else
   {
      TitanRenderSimplifiedCheck(dispbuffer, 0, tt_context.vdp2height, can_use_simplified_rendering);
   }
}