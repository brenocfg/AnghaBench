#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int left; unsigned int right; int enable; } ;

/* Variables and functions */
 TYPE_1__* clip ; 

void window_clip(unsigned int data, unsigned int sw)
{
  /* Window size and invert flags */
  int hp = (data & 0x1f);
  int hf = (data >> 7) & 1;

  /* Perform horizontal clipping; the results are applied in reverse
     if the horizontal inversion flag is set
   */
  int a = hf;
  int w = hf ^ 1;

  /* Display width (16 or 20 columns) */
  sw = 16 + (sw << 2);

  if(hp)
  {
    if(hp > sw)
    {
      /* Plane W takes up entire line */
      clip[w].left = 0;
      clip[w].right = sw;
      clip[w].enable = 1;
      clip[a].enable = 0;
    }
    else
    {
      /* Plane W takes left side, Plane A takes right side */
      clip[w].left = 0;
      clip[a].right = sw;
      clip[a].left = clip[w].right = hp;
      clip[0].enable = clip[1].enable = 1;
    }
  }
  else
  {
    /* Plane A takes up entire line */
    clip[a].left = 0;
    clip[a].right = sw;
    clip[a].enable = 1;
    clip[w].enable = 0;
  }
}