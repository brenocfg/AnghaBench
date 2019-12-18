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
typedef  int* src ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
typedef  int* dst ;

/* Variables and functions */
 int V4L2_FIELD_BOTTOM ; 
 int V4L2_FIELD_TOP ; 
 int* frame_prev1 ; 
 int* frame_prev2 ; 
 int* frame_prev3 ; 

void processing_deinterlacing_crap(uint32_t *src, uint32_t *dst, int width, int height, enum v4l2_field field, int skip_lines_src) {
   int i, targetrow=0;
   uint32_t pixacul=0;
   uint32_t *fp1 = frame_prev1, *fp2 = frame_prev2, *fp3 = frame_prev3;

   /* Helps pointing to the pixel in the adjacent row */
   if (field == V4L2_FIELD_TOP)
      targetrow = width;
   else
      targetrow = width*-1;

   /* Starts from the even scanline if frame contains bottom fields
    * On progressive sources, should only skip the destination lines, since all lines the source are the same fields
    * On interlaced sources, should skip both the source and the destination lines, since only half the lines in the source are the same fields (must also skip fields later)
    */
   if (field == V4L2_FIELD_BOTTOM) {
      dst += width;
      if (skip_lines_src == 1) {
         src += width;
         fp1 += width;
         fp2 += width;
         fp3 += width;
      }
   }

   for (i = 0; i < width * height; i+=1, src += 1, dst += 1, ++fp1, ++fp2, ++fp3) {
      /* Will fill the current destination line with current field
       * The masking is used to prserve some information set by the
       * deinterlacing process, uses the alpha channel to tell if a
       * pixel needs further processing...
       */
      *(dst) =  (*(src) & 0x00FFFFFF) | (*dst & 0xFF000000);

      /* Crappy deinterlacing */
      if (i >= width && i <= (width*height-width)) {
         pixacul=((((*(dst)>> 0&0xFF) + (pixacul>> 0&0xFF))>>1<<0 |\
                   ((*(dst)>> 8&0xFF) + (pixacul>> 8&0xFF))>>1<<8 |\
                   ((*(dst)>>16&0xFF) + (pixacul>>16&0xFF))>>1<<16) \
                   & 0x00FFFFFF) | 0xFE000000;

         if ( ((*(dst          ) & 0xFF000000) == 0xFE000000) ||\
              ((*(dst+targetrow) & 0xFF000000) == 0xFE000000) )  {
            *dst = pixacul | 0xFF000000;
            *(dst+targetrow) = pixacul | 0xFF000000;
         } else {
            if (!(((*(src+0)>> 0&0xFF) >= ((*(fp2+0)>> 0&0xFF)-9) ) &&\
                  ((*(src+0)>> 8&0xFF) >= ((*(fp2+0)>> 8&0xFF)-9) ) &&\
                  ((*(src+0)>>16&0xFF) >= ((*(fp2+0)>>16&0xFF)-9) ) &&\
                  ((*(src+0)>> 0&0xFF) <= ((*(fp2+0)>> 0&0xFF)+9) ) &&\
                  ((*(src+0)>> 8&0xFF) <= ((*(fp2+0)>> 8&0xFF)+9) ) &&\
                  ((*(src+0)>>16&0xFF) <= ((*(fp2+0)>>16&0xFF)+9) )) ) {
               *(dst+targetrow) = pixacul;
            } else if (!(((*fp3>> 0&0xFF) >= ((*fp1>> 0&0xFF)-9) ) &&\
                         ((*fp3>> 8&0xFF) >= ((*fp1>> 8&0xFF)-9) ) &&\
                         ((*fp3>>16&0xFF) >= ((*fp1>>16&0xFF)-9) ) &&\
                         ((*fp3>> 0&0xFF) <= ((*fp1>> 0&0xFF)+9) ) &&\
                         ((*fp3>> 8&0xFF) <= ((*fp1>> 8&0xFF)+9) ) &&\
                         ((*fp3>>16&0xFF) <= ((*fp1>>16&0xFF)+9) ))) {
               *(dst+targetrow) = pixacul;
            }
         }
      }

      /* Skips a scanline if we reach the end of the current one
       * On progressive sources, should only skip the destination lines,
       * On interlaced sources, should skip both the source and the destination lines
       */
      if ( ((i+1) % width) == 0 ) {
         dst += width;
         if (skip_lines_src == 1) {
            src += width;
            fp1 += width;
            fp2 += width;
            fp3 += width;
         }
      }
   }
}