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
 scalar_t__ stbi__flip_vertically_on_write ; 
 int /*<<< orphan*/  stbiw__paeth (unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static void stbiw__encode_png_line(unsigned char *pixels, int stride_bytes, int width, int height, int y, int n, int filter_type, signed char *line_buffer)
{
   static int mapping[] = { 0,1,2,3,4 };
   static int firstmap[] = { 0,1,0,5,6 };
   int *mymap = (y != 0) ? mapping : firstmap;
   int i;
   int type = mymap[filter_type];
   unsigned char *z = pixels + stride_bytes * (stbi__flip_vertically_on_write ? height-1-y : y);
   int signed_stride = stbi__flip_vertically_on_write ? -stride_bytes : stride_bytes;
   for (i = 0; i < n; ++i) {
      switch (type) {
         case 0: line_buffer[i] = z[i]; break;
         case 1: line_buffer[i] = z[i]; break;
         case 2: line_buffer[i] = z[i] - z[i-signed_stride]; break;
         case 3: line_buffer[i] = z[i] - (z[i-signed_stride]>>1); break;
         case 4: line_buffer[i] = (signed char) (z[i] - stbiw__paeth(0,z[i-signed_stride],0)); break;
         case 5: line_buffer[i] = z[i]; break;
         case 6: line_buffer[i] = z[i]; break;
      }
   }
   for (i=n; i < width*n; ++i) {
      switch (type) {
         case 0: line_buffer[i] = z[i]; break;
         case 1: line_buffer[i] = z[i] - z[i-n]; break;
         case 2: line_buffer[i] = z[i] - z[i-signed_stride]; break;
         case 3: line_buffer[i] = z[i] - ((z[i-n] + z[i-signed_stride])>>1); break;
         case 4: line_buffer[i] = z[i] - stbiw__paeth(z[i-n], z[i-signed_stride], z[i-signed_stride-n]); break;
         case 5: line_buffer[i] = z[i] - (z[i-n]>>1); break;
         case 6: line_buffer[i] = z[i] - stbiw__paeth(z[i-n], 0,0); break;
      }
   }
}