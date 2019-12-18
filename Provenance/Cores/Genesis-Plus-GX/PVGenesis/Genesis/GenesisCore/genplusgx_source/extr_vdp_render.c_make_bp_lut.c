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
typedef  int /*<<< orphan*/  uint32 ;

/* Variables and functions */
 int /*<<< orphan*/ * bp_lut ; 

__attribute__((used)) static void make_bp_lut(void)
{
  int x,i,j;
  uint32 out;

  /* ---------------------- */
  /* Pattern color encoding */
  /* -------------------------------------------------------------------------*/
  /* 4 byteplanes are required to define one pattern line (8 pixels)          */
  /* A single pixel color is coded with 4 bits (c3 c2 c1 c0)                  */
  /* Each bit is coming from byteplane bits, as explained below:              */
  /* pixel 0: c3 = bp3 bit 7, c2 = bp2 bit 7, c1 = bp1 bit 7, c0 = bp0 bit 7  */
  /* pixel 1: c3 = bp3 bit 6, c2 = bp2 bit 6, c1 = bp1 bit 6, c0 = bp0 bit 6  */
  /* ...                                                                      */
  /* pixel 7: c3 = bp3 bit 0, c2 = bp2 bit 0, c1 = bp1 bit 0, c0 = bp0 bit 0  */
  /* -------------------------------------------------------------------------*/

  for(i = 0; i < 0x100; i++)
  for(j = 0; j < 0x100; j++)
  {
    out = 0;
    for(x = 0; x < 8; x++)
    {
      /* pixel line data = hh00gg00ff00ee00dd00cc00bb00aa00 (32-bit) */
      /* aa-hh = upper or lower 2-bit values of pixels 0-7 (shifted) */
      out |= (j & (0x80 >> x)) ? (uint32)(8 << (x << 2)) : 0;
      out |= (i & (0x80 >> x)) ? (uint32)(4 << (x << 2)) : 0;
    }

    /* i = low byte in VRAM  (bp0 or bp2) */
    /* j = high byte in VRAM (bp1 or bp3) */
 #ifdef LSB_FIRST
    bp_lut[(j << 8) | (i)] = out;
 #else
    bp_lut[(i << 8) | (j)] = out;
 #endif
   }
}