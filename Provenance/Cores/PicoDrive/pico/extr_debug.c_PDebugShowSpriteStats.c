#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  pal; } ;
struct TYPE_6__ {TYPE_2__ video; TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLUE1 ; 
 int /*<<< orphan*/  GREEN1 ; 
 unsigned char** HighLnSpr ; 
 int MAX_LINE_SPRITES ; 
 TYPE_3__ Pico ; 
 int /*<<< orphan*/  RED1 ; 
 int /*<<< orphan*/  YELLOW1 ; 
 int /*<<< orphan*/  set16 (unsigned short*,int /*<<< orphan*/ ,int) ; 

void PDebugShowSpriteStats(unsigned short *screen, int stride)
{
  int lines, i, u, step;
  unsigned short *dest;
  unsigned char *p;

  step = (320-4*4-1) / MAX_LINE_SPRITES;
  lines = 240;
  if (!Pico.m.pal || !(Pico.video.reg[1]&8))
    lines = 224, screen += stride*8;

  for (i = 0; i < lines; i++)
  {
    dest = screen + stride*i;
    p = &HighLnSpr[i][0];

    // sprite graphs
    for (u = 0; u < (p[0] & 0x7f); u++) {
      set16(dest, (p[3+u] & 0x80) ? YELLOW1 : GREEN1, step);
      dest += step;
    }

    // flags
    dest = screen + stride*i + 320-4*4;
    if (p[1] & 0x40) set16(dest+4*0, GREEN1,  4);
    if (p[1] & 0x80) set16(dest+4*1, YELLOW1, 4);
    if (p[1] & 0x20) set16(dest+4*2, BLUE1,   4);
    if (p[1] & 0x10) set16(dest+4*3, RED1,    4);
  }

  // draw grid
  for (i = step*5; i <= 320-4*4-1; i += step*5) {
    for (u = 0; u < lines; u++)
      screen[i + u*stride] = 0x182;
  }
}