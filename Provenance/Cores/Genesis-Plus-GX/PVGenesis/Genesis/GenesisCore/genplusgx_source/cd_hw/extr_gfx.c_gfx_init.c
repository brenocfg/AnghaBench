#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
typedef  int uint16 ;
typedef  int /*<<< orphan*/  gfx_t ;
struct TYPE_3__ {int* lut_offset; int*** lut_prio; int* lut_cell; int* lut_pixel; } ;

/* Variables and functions */
 TYPE_1__ gfx ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void gfx_init(void)
{
  int i, j;
  uint16 offset;
  uint8 mask, row, col, temp;

  memset(&gfx, 0, sizeof(gfx_t));

  /* Initialize cell image lookup table */
  /* $220000-$22FFFF corresponds to $200000-$20FFFF */
  for (i=0; i<0x4000; i++)
  {
    offset = (i & 0x07) << 8;                     /* cell vline (0-7) */ 
    offset = offset | (((i >> 8) & 0x3f) << 2);   /* cell x offset (0-63) */
    offset = offset | (((i >> 3) & 0x1f) << 11);  /* cell y offset (0-31) */
    gfx.lut_offset[i] = offset;
  }
  
  /* $230000-$237FFF corresponds to $210000-$217FFF */
  for (i=0x4000; i<0x6000; i++)
  {
    offset = (i & 0x07) << 8;                     /* cell vline (0-7) */ 
    offset = offset | (((i >> 7) & 0x3f) << 2);   /* cell x offset (0-63) */
    offset = offset | (((i >> 3) & 0x0f) << 11);  /* cell y offset (0-15) */
    gfx.lut_offset[i] = offset;
  }

  /* $238000-$23BFFF corresponds to $218000-$21BFFF */
  for (i=0x6000; i<0x7000; i++)
  {
    offset = (i & 0x07) << 8;                     /* cell vline (0-7) */ 
    offset = offset | (((i >> 6) & 0x3f) << 2);   /* cell x offset (0-63) */
    offset = offset | (((i >> 3) & 0x07) << 11);  /* cell y offset (0-7) */
    gfx.lut_offset[i] = offset | 0x8000;
  }

  /* $23C000-$23DFFF corresponds to $21C000-$21DFFF */
  for (i=0x7000; i<0x7800; i++)
  {
    offset = (i & 0x07) << 8;                     /* cell vline (0-7) */ 
    offset = offset | (((i >> 5) & 0x3f) << 2);   /* cell x offset (0-63) */
    offset = offset | (((i >> 3) & 0x03) << 11);  /* cell y offset (0-3) */
    gfx.lut_offset[i] = offset | 0xc000;
  }

  /* $23E000-$23FFFF corresponds to $21E000-$21FFFF */
  for (i=0x7800; i<0x8000; i++)
  {
    offset = (i & 0x07) << 8;                     /* cell vline (0-7) */ 
    offset = offset | (((i >> 5) & 0x3f) << 2);   /* cell x offset (0-63) */
    offset = offset | (((i >> 3) & 0x03) << 11);  /* cell y offset (0-3) */
    gfx.lut_offset[i] = offset | 0xe000;
  }

  /* Initialize priority modes lookup table */
  for (i=0; i<0x100; i++)
  {
    for (j=0; j<0x100; j++)
    {
      /* normal */
      gfx.lut_prio[0][i][j] = j;
      /* underwrite */
      gfx.lut_prio[1][i][j] = ((i & 0x0f) ? (i & 0x0f) : (j & 0x0f)) | ((i & 0xf0) ? (i & 0xf0) : (j & 0xf0));
      /* overwrite */
      gfx.lut_prio[2][i][j] = ((j & 0x0f) ? (j & 0x0f) : (i & 0x0f)) | ((j & 0xf0) ? (j & 0xf0) : (i & 0xf0));
      /* invalid */
      gfx.lut_prio[3][i][j] = i;
    }
  }

  /* Initialize cell lookup table             */
  /* table entry = yyxxshrr (8 bits)          */
  /* with: yy = cell row (0-3)                */
  /*       xx = cell column (0-3)             */
  /*        s = stamp size (0=16x16, 1=32x32) */
  /*      hrr = HFLIP & ROTATION bits         */
  for (i=0; i<0x100; i++)
  {
    /* one stamp = 2x2 cells (16x16) or 4x4 cells (32x32) */
    mask = (i & 8) ? 3 : 1;
    row = (i >> 6) & mask;
    col = (i >> 4) & mask;

    if (i & 4) { col = col ^ mask; }  /* HFLIP (always first)  */ 
    if (i & 2) { col = col ^ mask; row = row ^ mask; }  /* ROLL1 */
    if (i & 1) { temp = col; col = row ^ mask; row = temp; }  /* ROLL0  */

    /* cell offset (0-3 or 0-15) */
    gfx.lut_cell[i] = row + col * (mask + 1);
  }

  /* Initialize pixel lookup table      */
  /* table entry = yyyxxxhrr (9 bits)   */
  /* with:  yyy = pixel row  (0-7)      */
  /*        xxx = pixel column (0-7)    */
  /*        hrr = HFLIP & ROTATION bits */
  for (i=0; i<0x200; i++)
  {
    /* one cell = 8x8 pixels */
    row = (i >> 6) & 7;
    col = (i >> 3) & 7;

    if (i & 4) { col = col ^ 7; }   /* HFLIP (always first) */ 
    if (i & 2) { col = col ^ 7; row = row ^ 7; }  /* ROLL1 */
    if (i & 1) { temp = col; col = row ^ 7; row = temp; } /* ROLL0 */

    /* pixel offset (0-63) */
    gfx.lut_pixel[i] = col + row * 8;
  }
}