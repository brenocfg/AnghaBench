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
struct TYPE_4__ {int w; int x; int h; int y; scalar_t__ changed; } ;
struct TYPE_6__ {scalar_t__ remap; TYPE_1__ viewport; } ;
struct TYPE_5__ {scalar_t__ scanlines; scalar_t__ vsync; } ;

/* Variables and functions */
 int SCREEN_H ; 
 int SCREEN_W ; 
 TYPE_3__ bitmap ; 
 int /*<<< orphan*/  blit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_to_color (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dos_update_palette () ; 
 int /*<<< orphan*/  frame_rate ; 
 int /*<<< orphan*/  gen_bmp ; 
 scalar_t__ interlaced ; 
 int /*<<< orphan*/  msg_print (int,int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ option ; 
 int /*<<< orphan*/  screen ; 
 int /*<<< orphan*/  stretch_blit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  vsync () ; 

void dos_update_video(void)
{
  int width = (bitmap.viewport.w + 2 * bitmap.viewport.x);
  int height = (bitmap.viewport.h + 2 * bitmap.viewport.y) << (interlaced ? 1:0);
  int center_x = (SCREEN_W - width) / 2;
  int center_y = (SCREEN_H / (option.scanlines ? 4 : 2)) - (height / 2);

  /* Wait for VSync */
  if(option.vsync) vsync();

  if(bitmap.viewport.changed)
  {
    bitmap.viewport.changed = 0;
    if(bitmap.remap)
    {
      clear(screen);
    }
    else
    {
      clear_to_color(screen, 0xFF);
    }
  }

#if 0
  if(bitmap.remap == 0)
  {
  dos_update_palette();
  }
#endif

  msg_print(2, 2, "%d", frame_rate);

  if(option.scanlines)
  {
    int y;
    for(y = 0; y < height; y += 1)
    {
      blit(gen_bmp, screen, 0x0, y, center_x, (center_y + y) << 1, width, 1);
    }
  }
  else
  {
    stretch_blit(gen_bmp, screen, 0, 0, width, height, (SCREEN_W-352)/2, (SCREEN_H-240)/2, 352,240 << (interlaced ? 1:0));
  }
}