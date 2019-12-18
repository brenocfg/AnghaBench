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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int FBCR; int TVMR; } ;
typedef  TYPE_1__ Vdp1 ;

/* Variables and functions */
 int /*<<< orphan*/  VIDSoftVdp1EraseFrameBuffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int vdp1height ; 
 int vdp1interlace ; 
 int vdp1pixelsize ; 
 int vdp1width ; 

void VIDSoftVdp1DrawStartBody(Vdp1* regs, u8 * back_framebuffer)
{
   if (regs->FBCR & 8)
      vdp1interlace = 2;
   else
      vdp1interlace = 1;
   if (regs->TVMR & 0x1)
   {
      if (regs->TVMR & 0x2)
      {
         // Rotation 8-bit
         vdp1width = 512;
         vdp1height = 512;
      }
      else
      {
         // Normal 8-bit
         vdp1width = 1024;
         vdp1height = 256;
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

   VIDSoftVdp1EraseFrameBuffer(regs, back_framebuffer);

   //night warriors doesn't set clipping most frames and uses
   //the last part of the vdp1 framebuffer as scratch ram
   //the previously set clipping values need to be reused
}