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
 unsigned int* pixel ; 
 void*** pixel_lut ; 
 int* reg ; 

void color_update_m5(int index, unsigned int data)
{
  /* Palette Mode */
  if (!(reg[0] & 0x04))
  {
    /* Color value is limited to 00X00X00X */
    data &= 0x49;
  }

  if(reg[12] & 0x08)
  {
    /* Mode 5 (Shadow/Normal/Highlight) */
    pixel[0x00 | index] = pixel_lut[0][data];
    pixel[0x40 | index] = pixel_lut[1][data];
    pixel[0x80 | index] = pixel_lut[2][data];
  }
  else
  {
    /* Mode 5 (Normal) */
    data = pixel_lut[1][data];

    /* Input pixel: xxiiiiii */
    pixel[0x00 | index] = data;
    pixel[0x40 | index] = data;
    pixel[0x80 | index] = data;
  }
}