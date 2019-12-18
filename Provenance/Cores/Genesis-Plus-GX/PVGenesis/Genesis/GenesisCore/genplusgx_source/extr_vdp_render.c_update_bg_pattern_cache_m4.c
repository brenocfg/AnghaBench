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
typedef  int uint8 ;
typedef  int uint32 ;
typedef  size_t uint16 ;

/* Variables and functions */
 int* bg_name_dirty ; 
 size_t* bg_name_list ; 
 int* bg_pattern_cache ; 
 int* bp_lut ; 
 int /*<<< orphan*/ * vram ; 

void update_bg_pattern_cache_m4(int index)
{
  int i;
  uint8 x, y, c;
  uint8 *dst;
  uint16 name, bp01, bp23;
  uint32 bp;

  for(i = 0; i < index; i++)
  {
    /* Get modified pattern name index */
    name = bg_name_list[i];

    /* Check modified lines */
    for(y = 0; y < 8; y++)
    {
      if(bg_name_dirty[name] & (1 << y))
      {
        /* Pattern cache base address */
        dst = &bg_pattern_cache[name << 6];

        /* Byteplane data */
        bp01 = *(uint16 *)&vram[(name << 5) | (y << 2) | (0)];
        bp23 = *(uint16 *)&vram[(name << 5) | (y << 2) | (2)];

        /* Convert to pixel line data (4 bytes = 8 pixels)*/
        /* (msb) p7p6 p5p4 p3p2 p1p0 (lsb) */
        bp = (bp_lut[bp01] >> 2) | (bp_lut[bp23]);

        /* Update cached line (8 pixels = 8 bytes) */
        for(x = 0; x < 8; x++)
        {
          /* Extract pixel data */
          c = bp & 0x0F;

          /* Pattern cache data (one pattern = 8 bytes) */
          /* byte0 <-> p0 p1 p2 p3 p4 p5 p6 p7 <-> byte7 (hflip = 0) */
          /* byte0 <-> p7 p6 p5 p4 p3 p2 p1 p0 <-> byte7 (hflip = 1) */
          dst[0x00000 | (y << 3) | (x)] = (c);            /* vflip=0 & hflip=0 */
          dst[0x08000 | (y << 3) | (x ^ 7)] = (c);        /* vflip=0 & hflip=1 */
          dst[0x10000 | ((y ^ 7) << 3) | (x)] = (c);      /* vflip=1 & hflip=0 */
          dst[0x18000 | ((y ^ 7) << 3) | (x ^ 7)] = (c);  /* vflip=1 & hflip=1 */

          /* Next pixel */
          bp = bp >> 4;
        }
      }
    }

    /* Clear modified pattern flag */
    bg_name_dirty[name] = 0;
  }
}