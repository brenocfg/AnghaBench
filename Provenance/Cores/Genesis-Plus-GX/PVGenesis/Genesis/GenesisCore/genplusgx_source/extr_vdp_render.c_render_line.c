#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int w; int h; int x; } ;
struct TYPE_4__ {TYPE_1__ viewport; } ;

/* Variables and functions */
 scalar_t__ SYSTEM_MD ; 
 scalar_t__ SYSTEM_SG ; 
 scalar_t__ bg_list_index ; 
 TYPE_2__ bitmap ; 
 int /*<<< orphan*/ ** linebuf ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  parse_satb (int) ; 
 int* reg ; 
 int /*<<< orphan*/  remap_line (int) ; 
 int /*<<< orphan*/  render_bg (int,int) ; 
 int /*<<< orphan*/  render_obj (int) ; 
 int /*<<< orphan*/  spr_ovr ; 
 int /*<<< orphan*/  status ; 
 scalar_t__ system_hw ; 
 int /*<<< orphan*/  update_bg_pattern_cache (scalar_t__) ; 

void render_line(int line)
{
  int width = bitmap.viewport.w;
  int x_offset;

  /* Check display status */
  if (reg[1] & 0x40)
  {
    /* Update pattern cache */
    if (bg_list_index)
    {
      update_bg_pattern_cache(bg_list_index);
      bg_list_index = 0;
    }

    /* Render BG layer(s) */
    render_bg(line, width);

    /* Render sprite layer */
    render_obj(width);

    /* Left-most column blanking */
    if (reg[0] & 0x20)
    {
      if (system_hw > SYSTEM_SG)
      {
        memset(&linebuf[0][0x20], 0x40, 8);
      }
    }

    /* Parse sprites for next line */
    if (line < (bitmap.viewport.h - 1))
    {
      parse_satb(line);
    }
  }
  else
  {
    /* Master System & Game Gear VDP specific */
    if (system_hw < SYSTEM_MD)
    {
      /* Update SOVR flag */
      status |= spr_ovr;
      spr_ovr = 0;

      /* Sprites are still parsed when display is disabled */
      parse_satb(line);
    }

    /* Blanked line */
    memset(&linebuf[0][0x20], 0x40, width);
  }

  /* Horizontal borders */
  x_offset = bitmap.viewport.x;
  if (x_offset > 0)
  {
    memset(&linebuf[0][0x20 - x_offset], 0x40, x_offset);
    memset(&linebuf[0][0x20 + width], 0x40, x_offset);
  }

  /* Pixel color remapping */
  remap_line(line);
}