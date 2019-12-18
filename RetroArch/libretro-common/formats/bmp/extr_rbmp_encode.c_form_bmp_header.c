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
typedef  char uint8_t ;

/* Variables and functions */

void form_bmp_header(uint8_t *header,
      unsigned width, unsigned height,
      bool is32bpp)
{
   unsigned line_size  = (width * (is32bpp?4:3) + 3) & ~3;
   unsigned size       = line_size * height + 54;
   unsigned size_array = line_size * height;

   /* Generic BMP stuff. */
   /* signature */
   header[0] = 'B';
   header[1] = 'M';
   /* file size */
   header[2] = (uint8_t)(size >> 0);
   header[3] = (uint8_t)(size >> 8);
   header[4] = (uint8_t)(size >> 16);
   header[5] = (uint8_t)(size >> 24);
   /* reserved */
   header[6] = 0;
   header[7] = 0;
   header[8] = 0;
   header[9] = 0;
   /* offset */
   header[10] = 54;
   header[11] = 0;
   header[12] = 0;
   header[13] = 0;
   /* DIB size */
   header[14] = 40;
   header[15] = 0;
   header[16] = 0;
   header[17] = 0;
   /* Width */
   header[18] = (uint8_t)(width >> 0);
   header[19] = (uint8_t)(width >> 8);
   header[20] = (uint8_t)(width >> 16);
   header[21] = (uint8_t)(width >> 24);
   /* Height */
   header[22] = (uint8_t)(height >> 0);
   header[23] = (uint8_t)(height >> 8);
   header[24] = (uint8_t)(height >> 16);
   header[25] = (uint8_t)(height >> 24);
   /* Color planes */
   header[26] = 1;
   header[27] = 0;
   /* Bits per pixel */
   header[28] = is32bpp ? 32 : 24;
   header[29] = 0;
   /* Compression method */
   header[30] = 0;
   header[31] = 0;
   header[32] = 0;
   header[33] = 0;
   /* Image data size */
   header[34] = (uint8_t)(size_array >> 0);
   header[35] = (uint8_t)(size_array >> 8);
   header[36] = (uint8_t)(size_array >> 16);
   header[37] = (uint8_t)(size_array >> 24);
   /* Horizontal resolution */
   header[38] = 19;
   header[39] = 11;
   header[40] = 0;
   header[41] = 0;
   /* Vertical resolution */
   header[42] = 19;
   header[43] = 11;
   header[44] = 0;
   header[45] = 0;
   /* Palette size */
   header[46] = 0;
   header[47] = 0;
   header[48] = 0;
   header[49] = 0;
   /* Important color count */
   header[50] = 0;
   header[51] = 0;
   header[52] = 0;
   header[53] = 0;
}