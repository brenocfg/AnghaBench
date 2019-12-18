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
struct TYPE_2__ {int TVMR; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIDGCDVdp1EraseFrameBuffer () ; 
 TYPE_1__* Vdp1Regs ; 
 int vdp1height ; 
 int vdp1pixelsize ; 
 int vdp1width ; 

void VIDGCDVdp1DrawStart(void)
{
   if (Vdp1Regs->TVMR & 0x1)
   {
      if (Vdp1Regs->TVMR & 0x2)
      {
         // Rotation 8-bit
         vdp1width = 512;
         vdp1height = 512;
      }
      else
      {
         // Normal 8-bit
         vdp1width = 1024;
         vdp1width = 256;
      }

      vdp1pixelsize = 1;
   }
   else
   {
      // Rotation/Normal 16-bit
      vdp1width = 512;
      vdp1height = 256;
      vdp1pixelsize = 2;
   }

   VIDGCDVdp1EraseFrameBuffer();
}