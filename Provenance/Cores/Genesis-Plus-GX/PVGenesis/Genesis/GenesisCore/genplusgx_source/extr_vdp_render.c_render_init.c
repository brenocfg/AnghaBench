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
typedef  size_t uint16 ;

/* Variables and functions */
 int /*<<< orphan*/ ** lut ; 
 int /*<<< orphan*/  make_bp_lut () ; 
 int /*<<< orphan*/  make_lut_bg (int,int) ; 
 int /*<<< orphan*/  make_lut_bg_ste (int,int) ; 
 int /*<<< orphan*/  make_lut_bgobj (int,int) ; 
 int /*<<< orphan*/  make_lut_bgobj_m4 (int,int) ; 
 int /*<<< orphan*/  make_lut_bgobj_ste (int,int) ; 
 int /*<<< orphan*/  make_lut_obj (int,int) ; 
 int /*<<< orphan*/  make_name_lut () ; 
 int /*<<< orphan*/  palette_init () ; 

void render_init(void)
{
  int bx, ax;

  /* Initialize layers priority pixel look-up tables */
  uint16 index;
  for (bx = 0; bx < 0x100; bx++)
  {
    for (ax = 0; ax < 0x100; ax++)
    {
      index = (bx << 8) | (ax);

      lut[0][index] = make_lut_bg(bx, ax);
      lut[1][index] = make_lut_bgobj(bx, ax);
      lut[2][index] = make_lut_bg_ste(bx, ax);
      lut[3][index] = make_lut_obj(bx, ax);
      lut[4][index] = make_lut_bgobj_ste(bx, ax);
      lut[5][index] = make_lut_bgobj_m4(bx,ax);
    }
  }

  /* Initialize pixel color look-up tables */
  palette_init();

  /* Make sprite pattern name index look-up table (Mode 5) */
  make_name_lut();

  /* Make bitplane to pixel look-up table (Mode 4) */
  make_bp_lut();
}