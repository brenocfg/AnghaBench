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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void rbmp_convert_frame(uint32_t *frame, unsigned width, unsigned height)
{
   uint32_t *end = frame + (width * height * sizeof(uint32_t))/4;

   while(frame < end)
   {
      uint32_t pixel = *frame;
      *frame = (pixel & 0xff00ff00) | ((pixel << 16) & 0x00ff0000) | ((pixel >> 16) & 0xff);
      frame++;
   }
}