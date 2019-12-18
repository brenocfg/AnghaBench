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
struct TYPE_5__ {int w; int h; int x; int y; TYPE_2__* texture; } ;
typedef  TYPE_1__ gui_image ;
struct TYPE_7__ {char* filename; scalar_t__ flags; } ;
struct TYPE_6__ {int width; int height; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ BG_COLOR_1 ; 
 scalar_t__ BG_COLOR_2 ; 
 int /*<<< orphan*/  Browser_dir_png ; 
 scalar_t__ FONT_write (char*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  Overlay_bar_png ; 
 int SCROLL_SPEED ; 
 scalar_t__ WHITE ; 
 TYPE_4__* filelist ; 
 int /*<<< orphan*/  gxDrawRectangle (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxDrawTexture (TYPE_2__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  gxTextureClose (TYPE_2__**) ; 
 void* gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxfiles ; 
 int offset ; 
 int selection ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int string_offset ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static void selector_cb(void)
{
  int i;
  char text[MAXPATHLEN];
  int yoffset = 108;

  /* Initialize directory icon */
  gui_image dir_icon;
  dir_icon.texture = gxTextureOpenPNG(Browser_dir_png,0);
  dir_icon.w = dir_icon.texture->width;
  dir_icon.h = dir_icon.texture->height;
  dir_icon.x = 26;
  dir_icon.y = (26 - dir_icon.h)/2;

  /* Initialize selection bar */
  gui_image bar_over;
  bar_over.texture = gxTextureOpenPNG(Overlay_bar_png,0);
  bar_over.w = bar_over.texture->width;
  bar_over.h = bar_over.texture->height;
  bar_over.x = 16;
  bar_over.y = (26 - bar_over.h)/2;

  /* Draw browser array */
  gxDrawRectangle(15, 108, 358, 26, 127, (GXColor)BG_COLOR_1);
  gxDrawRectangle(15, 134, 358, 26, 127, (GXColor)BG_COLOR_2);
  gxDrawRectangle(15, 160, 358, 26, 127, (GXColor)BG_COLOR_1);
  gxDrawRectangle(15, 186, 358, 26, 127, (GXColor)BG_COLOR_2);
  gxDrawRectangle(15, 212, 358, 26, 127, (GXColor)BG_COLOR_1);
  gxDrawRectangle(15, 238, 358, 26, 127, (GXColor)BG_COLOR_2);
  gxDrawRectangle(15, 264, 358, 26, 127, (GXColor)BG_COLOR_1);
  gxDrawRectangle(15, 290, 358, 26, 127, (GXColor)BG_COLOR_2);
  gxDrawRectangle(15, 316, 358, 26, 127, (GXColor)BG_COLOR_1);
  gxDrawRectangle(15, 342, 358, 26, 127, (GXColor)BG_COLOR_2);

  /* Draw Files list */
  for (i = offset; (i < (offset + 10)) && (i < maxfiles); i++)
  {
    if (i == selection)
    {
      /* selection bar */
      gxDrawTexture(bar_over.texture,bar_over.x,yoffset+bar_over.y,bar_over.w,bar_over.h,255);

      /* scrolling text */
      if ((string_offset/SCROLL_SPEED) >= strlen(filelist[i].filename))
      {
        string_offset = 0;
      }

      if (string_offset)
      {
        sprintf(text,"%s ",filelist[i].filename+string_offset/SCROLL_SPEED);
        strncat(text, filelist[i].filename, string_offset/SCROLL_SPEED);
      }
      else
      {
        strcpy(text, filelist[i].filename);
      }

      /* print text */
      if (filelist[i].flags)
      {
        /* directory icon */
        gxDrawTexture(dir_icon.texture,dir_icon.x,yoffset+dir_icon.y,dir_icon.w,dir_icon.h,255);
        if (FONT_write(text,18,dir_icon.x+dir_icon.w+6,yoffset+22,bar_over.w-dir_icon.w-26,(GXColor)WHITE))
        {
          /* text scrolling */
          string_offset ++;
        }
      }
      else
      {
        if (FONT_write(text,18,dir_icon.x,yoffset+22,bar_over.w-20,(GXColor)WHITE))
        {
          /* text scrolling */
          string_offset ++;
        }
      }
    }
    else
    {
      if (filelist[i].flags)
      {
        /* directory icon */
        gxDrawTexture(dir_icon.texture,dir_icon.x,yoffset+dir_icon.y,dir_icon.w,dir_icon.h,255);
        FONT_write(filelist[i].filename,18,dir_icon.x+dir_icon.w+6,yoffset+22,bar_over.w-dir_icon.w-26,(GXColor)WHITE);
      }
      else
      {
        FONT_write(filelist[i].filename,18,dir_icon.x,yoffset+22,bar_over.w-20,(GXColor)WHITE);
      }
    }

    yoffset += 26;
  }

  gxTextureClose(&bar_over.texture);
  gxTextureClose(&dir_icon.texture);
}