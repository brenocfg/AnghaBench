#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 unsigned int VGA_HEIGHT ; 
 unsigned int VGA_WIDTH ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (unsigned int) ; 
 int vga_menu_bits ; 
 unsigned char* vga_menu_frame ; 
 unsigned int vga_menu_height ; 
 unsigned int vga_menu_pitch ; 
 unsigned int vga_menu_width ; 

__attribute__((used)) static void vga_set_texture_frame(void *data,
      const void *frame, bool rgb32, unsigned width, unsigned height,
      float alpha)
{
   unsigned pitch = width * 2;

   if (rgb32)
      pitch = width * 4;

   if (vga_menu_frame)
   {
      free(vga_menu_frame);
      vga_menu_frame = NULL;
   }

   if ( !vga_menu_frame ||
         vga_menu_width  != width  ||
         vga_menu_height != height ||
         vga_menu_pitch  != pitch)
      if (pitch && height)
         vga_menu_frame = (unsigned char*)malloc(VGA_WIDTH * VGA_HEIGHT);

   if (vga_menu_frame && frame && pitch && height)
   {
      unsigned x, y;

      if (rgb32)
      {
      }
      else
      {
         unsigned short *video_frame = (unsigned short*)frame;

         for(y = 0; y < VGA_HEIGHT; y++)
         {
            for(x = 0; x < VGA_WIDTH; x++)
            {
               /* scale incoming frame to fit the screen */
               unsigned scaled_x = (width * x) / VGA_WIDTH;
               unsigned scaled_y = (height * y) / VGA_HEIGHT;
               unsigned short pixel = video_frame[width * scaled_y + scaled_x];
               unsigned r = ((pixel & 0xF000) >> 13);
               unsigned g = ((pixel & 0xF00) >> 9);
               unsigned b = ((pixel & 0xF0) >> 6);
               vga_menu_frame[VGA_WIDTH * y + x] = (b << 6) | (g << 3) | r;
            }
         }
      }

      vga_menu_width  = width;
      vga_menu_height = height;
      vga_menu_pitch  = pitch;
      vga_menu_bits   = rgb32 ? 32 : 16;
   }
}