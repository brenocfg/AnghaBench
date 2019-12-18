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
 int* name_lut ; 

__attribute__((used)) static void make_name_lut(void)
{
  int vcol, vrow;
  int width, height;
  int flipx, flipy;
  int i;

  for (i = 0; i < 0x400; i += 1)
  {
    /* Sprite settings */
    vcol = i & 3;
    vrow = (i >> 2) & 3;
    height = (i >> 4) & 3;
    width  = (i >> 6) & 3;
    flipx  = (i >> 8) & 1;
    flipy  = (i >> 9) & 1;

    if ((vrow > height) || vcol > width)
    {
      /* Invalid settings (unused) */
      name_lut[i] = -1; 
    }
    else
    {
      /* Adjust column & row index if sprite is flipped */
      if(flipx) vcol = (width - vcol);
      if(flipy) vrow = (height - vrow);

      /* Pattern offset (pattern order is up->down->left->right) */
      name_lut[i] = vrow + (vcol * (height + 1));
    }
  }
}