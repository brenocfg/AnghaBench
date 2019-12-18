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
typedef  int u32 ;
struct PixelData {int priority; int linescreen; int pixel; scalar_t__ shadow_type; scalar_t__ shadow_enabled; } ;
struct TYPE_4__ {int SPCTL; } ;
struct TYPE_3__ {int (* blend ) (int,int) ;int** linescreen; scalar_t__ (* trans ) (int) ;struct PixelData* backscreen; struct PixelData** vdp2framebuffer; } ;

/* Variables and functions */
 scalar_t__ TITAN_MSB_SHADOW ; 
 scalar_t__ TITAN_NORMAL_SHADOW ; 
 int TITAN_SPRITE ; 
 void* TitanBlendPixelsTop (int,int) ; 
 TYPE_2__* Vdp2Regs ; 
 int stub1 (int,int) ; 
 scalar_t__ stub2 (int) ; 
 int stub3 (int,int) ; 
 scalar_t__ stub4 (int) ; 
 int stub5 (int,int) ; 
 TYPE_1__ tt_context ; 

__attribute__((used)) static u32 TitanDigPixel(int pos, int y)
{
   struct PixelData pixel_stack[2] = { 0 };

   int pixel_stack_pos = 0;

   int priority;

   //sort the pixels from highest to lowest priority
   for (priority = 7; priority > 0; priority--)
   {
      int which_layer;

      for (which_layer = TITAN_SPRITE; which_layer >= 0; which_layer--)
      {
         if (tt_context.vdp2framebuffer[which_layer][pos].priority == priority)
         {
            pixel_stack[pixel_stack_pos] = tt_context.vdp2framebuffer[which_layer][pos];
            pixel_stack_pos++;

            if (pixel_stack_pos == 2)
               goto finished;//backscreen is unnecessary in this case
         }
      }
   }

   pixel_stack[pixel_stack_pos] = tt_context.backscreen[pos];

finished:

   if (pixel_stack[0].linescreen)
   {
      pixel_stack[0].pixel = tt_context.blend(pixel_stack[0].pixel, tt_context.linescreen[pixel_stack[0].linescreen][y]);
   }

   if ((pixel_stack[0].shadow_type == TITAN_MSB_SHADOW) && ((pixel_stack[0].pixel & 0xFFFFFF) == 0))
   {
      //transparent sprite shadow
      if (pixel_stack[1].shadow_enabled)
      {
         pixel_stack[0].pixel = TitanBlendPixelsTop(0x20000000, pixel_stack[1].pixel);
      }
      else
      {
         pixel_stack[0].pixel = pixel_stack[1].pixel;
      }
   }
   else if (pixel_stack[0].shadow_type == TITAN_MSB_SHADOW && ((pixel_stack[0].pixel & 0xFFFFFF) != 0))
   {
      if (tt_context.trans(pixel_stack[0].pixel))
      {
         u32 bottom = pixel_stack[1].pixel;
         pixel_stack[0].pixel = tt_context.blend(pixel_stack[0].pixel, bottom);
      }

      //sprite self-shadowing, only if sprite window is not enabled
      if (!(Vdp2Regs->SPCTL & 0x10))
         pixel_stack[0].pixel = TitanBlendPixelsTop(0x20000000, pixel_stack[0].pixel);
   }
   else if (pixel_stack[0].shadow_type == TITAN_NORMAL_SHADOW)
   {
      if (pixel_stack[1].shadow_enabled)
      {
         pixel_stack[0].pixel = TitanBlendPixelsTop(0x20000000, pixel_stack[1].pixel);
      }
      else
      {
         pixel_stack[0].pixel = pixel_stack[1].pixel;
      }
   }
   else
   {
      if (tt_context.trans(pixel_stack[0].pixel))
      {
         u32 bottom = pixel_stack[1].pixel;
         pixel_stack[0].pixel = tt_context.blend(pixel_stack[0].pixel, bottom);
      }
   }

   return pixel_stack[0].pixel;
}