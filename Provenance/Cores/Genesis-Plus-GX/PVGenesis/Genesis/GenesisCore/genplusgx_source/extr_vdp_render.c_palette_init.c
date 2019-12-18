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
 void* MAKE_PIXEL (int,int,int) ; 
 void*** pixel_lut ; 
 void** pixel_lut_m4 ; 

__attribute__((used)) static void palette_init(void)
{
  int r, g, b, i;

  /************************************************/
  /* Each R,G,B color channel is 4-bit with a     */
  /* total of 15 different intensity levels.      */
  /*                                              */
  /* Color intensity depends on the mode:         */
  /*                                              */
  /*    normal   : xxx0     (0-14)                */
  /*    shadow   : 0xxx     (0-7)                 */
  /*    highlight: 1xxx - 1 (7-14)                */
  /*    mode4    : xx00 ?   (0-12)                */
  /*    GG mode  : xxxx     (0-16)                */
  /*                                              */
  /* with x = original CRAM value (2, 3 or 4-bit) */
  /************************************************/

  /* Initialize Mode 5 pixel color look-up tables */
  for (i = 0; i < 0x200; i++)
  {
    /* CRAM 9-bit value (BBBGGGRRR) */
    r = (i >> 0) & 7;
    g = (i >> 3) & 7;
    b = (i >> 6) & 7;

    /* Convert to output pixel format */
    pixel_lut[0][i] = MAKE_PIXEL(r,g,b);
    pixel_lut[1][i] = MAKE_PIXEL(r<<1,g<<1,b<<1);
    pixel_lut[2][i] = MAKE_PIXEL(r+7,g+7,b+7);
  }

  /* Initialize Mode 4 pixel color look-up table */
  for (i = 0; i < 0x40; i++)
  {
    /* CRAM 6-bit value (000BBGGRR) */
    r = (i >> 0) & 3;
    g = (i >> 2) & 3;
    b = (i >> 4) & 3;

    /* Convert to output pixel format (expand to 4-bit for brighter colors ?) */
    pixel_lut_m4[i] = MAKE_PIXEL(r << 2,g << 2,b<< 2);
  }
}