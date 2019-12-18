#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int depth; scalar_t__ remap; } ;
struct TYPE_6__ {int video_width; int video_height; int video_depth; int /*<<< orphan*/  video_driver; scalar_t__ scanlines; } ;
struct TYPE_5__ {int r; int g; int b; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_TEXT ; 
 char* allegro_error ; 
 TYPE_4__ bitmap ; 
 int /*<<< orphan*/  clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_to_color (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 TYPE_1__* gen_pal ; 
 int /*<<< orphan*/  inp (int) ; 
 TYPE_2__ option ; 
 int /*<<< orphan*/  outp (int,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,char*) ; 
 int /*<<< orphan*/  screen ; 
 int set_gfx_mode (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_palette (TYPE_1__*) ; 

void dos_change_mode(void)
{
  int ret;
  int width = option.video_width;
  int height = option.video_height;

  if(option.scanlines) height *= 2;
  ret = set_gfx_mode(option.video_driver, width, height, 0, 0);
  if(ret != 0)
  {
    set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
    printf("Error setting graphics mode (%dx%d %dbpp).\nAllegro says: `%s'\n", width, height, option.video_depth, allegro_error);
    exit(1);
  }

  if(bitmap.depth == 8)
  {
    if(bitmap.remap)
    {
      int i;
      for(i = 0; i < 0x100; i += 1)
      {
        gen_pal[i].r = ((i >> 5) & 7) << 3;
        gen_pal[i].g = ((i >> 2) & 7) << 3;
        gen_pal[i].b = ((i >> 0) & 3) << 4;
      }
      set_palette(gen_pal);
    }
    else
    {
      clear_to_color(screen, 0xFF);
      gen_pal[0xfe].r = 0xff;
      gen_pal[0xfe].g = 0xff;
      gen_pal[0xfe].b = 0xff;
      set_palette(gen_pal);
      inp(0x3DA);
      outp(0x3C0, 0x31);
      outp(0x3C0, 0xFF);
    }
  }
  else
  {
    clear(screen);
  }
}