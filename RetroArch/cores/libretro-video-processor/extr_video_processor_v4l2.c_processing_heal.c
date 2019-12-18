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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* frame_prev1 ; 

void processing_heal(uint8_t *src, int width, int height) {
   uint32_t *fp1 = frame_prev1;
   int i;
   for (i = 0; i < width * height; i+=1, src += 3, ++fp1) {
      /* Tries to filter a bunch of blanked out scanline sections my capture cards spits out with this crazy hack
       * Since the blanked out scanlines are set to a black value bellow anything that can be captued, it's quite
       * easy to select the scanlines...
       */
      if (src[0] <= 0 && src[1] <= 0 && src[2] <= 0 && i >= width && i <= width * height - width) {
         if (*(src + 0 - width*3) >= ((*fp1>> 0&0xFF)-6) && \
             *(src + 1 - width*3) >= ((*fp1>> 8&0xFF)-6) && \
             *(src + 2 - width*3) >= ((*fp1>>16&0xFF)-6) && \
             *(src + 0 - width*3) <= ((*fp1>> 0&0xFF)+6) && \
             *(src + 1 - width*3) <= ((*fp1>> 8&0xFF)+6) && \
             *(src + 2 - width*3) <= ((*fp1>>16&0xFF)+6)) {
            src[0] = (*fp1>> 0&0xFF);
            src[1] = (*fp1>> 8&0xFF);
            src[2] = (*fp1>>16&0xFF);
         } else {
            src[0] = (*(fp1+i+width)>> 0&0xFF);
            src[1] = (*(fp1+i+width)>> 8&0xFF);
            src[2] = (*(fp1+i+width)>>16&0xFF);
         }
      }
   }
}