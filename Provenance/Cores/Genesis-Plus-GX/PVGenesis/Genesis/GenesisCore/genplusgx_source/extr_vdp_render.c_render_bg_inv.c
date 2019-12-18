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

/* Variables and functions */
 int** linebuf ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int* reg ; 

void render_bg_inv(int line, int width)
{
  uint8 color = reg[7];

  uint8 *lb = &linebuf[0][0x20];

  /* Left border (8 pixels) */
  memset (lb, 0x40, 8);
  lb += 8;

  /* 40 x 6 pixels */
  width = 40;

  do
  {
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 4) & 0x0F);
    *lb++ = 0x10 | ((color >> 0) & 0x0F);
    *lb++ = 0x10 | ((color >> 0) & 0x0F);
  }
  while (--width);

  /* Right borders (8 pixels) */
  memset(lb, 0x40, 8);
}