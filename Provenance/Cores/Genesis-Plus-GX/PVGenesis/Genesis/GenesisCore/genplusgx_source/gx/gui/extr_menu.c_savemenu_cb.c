#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ gx_texture ;
struct TYPE_13__ {int h; scalar_t__ y; scalar_t__ x; scalar_t__ w; } ;
struct TYPE_12__ {int s_default; } ;
struct TYPE_11__ {int day; int month; int year; int hour; int min; scalar_t__ valid; } ;
struct TYPE_10__ {scalar_t__ crc; int /*<<< orphan*/ * sram; scalar_t__ on; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ DARK_GREY ; 
 int /*<<< orphan*/  FONT_alignRight (char*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FONT_write (char*,int,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FONT_writeCenter (char*,int,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Star_full_png ; 
 TYPE_8__* buttons_saves ; 
 TYPE_7__ config ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gxDrawTexture (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gxTextureClose (TYPE_1__**) ; 
 TYPE_1__* gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* slots ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 TYPE_2__ sram ; 

__attribute__((used)) static void savemenu_cb(void)
{
  int i;
  char msg[16];
  gx_texture *star = gxTextureOpenPNG(Star_full_png,0);
  
  if (sram.on)
  {
    FONT_write("Backup Memory",16,buttons_saves[0].x+16,buttons_saves[0].y+(buttons_saves[0].h-16)/2+16,buttons_saves[0].x+buttons_saves[0].w,(GXColor)DARK_GREY);
    if (slots[0].valid)
    {
      sprintf(msg,"%d/%02d/%02d",slots[0].day,slots[0].month,slots[0].year);
      FONT_alignRight(msg,12,buttons_saves[0].x+buttons_saves[0].w-16,buttons_saves[0].y+(buttons_saves[0].h-28)/2+12,(GXColor)DARK_GREY);
      sprintf(msg,"%02d:%02d",slots[0].hour,slots[0].min);
      FONT_alignRight(msg,12,buttons_saves[0].x+buttons_saves[0].w-16,buttons_saves[0].y+(buttons_saves[0].h-28)/2+28,(GXColor)DARK_GREY);
    }

    if (sram.crc != crc32(0, &sram.sram[0], 0x10000))
      gxDrawTexture(star,22,buttons_saves[0].y+(buttons_saves[0].h-star->height)/2,star->width,star->height,255);
  }
  else
  {
    FONT_writeCenter("Backup Memory disabled",16,buttons_saves[0].x,buttons_saves[0].x+buttons_saves[0].w,buttons_saves[0].y+(buttons_saves[0].h-16)/2+16,(GXColor)DARK_GREY);
  }

  for (i=1; i<5; i++)
  {
    if (slots[i].valid)
    {
      sprintf(msg,"Slot %d",i);
      FONT_write(msg,16,buttons_saves[i].x+16,buttons_saves[i].y+(buttons_saves[i].h-16)/2+16,buttons_saves[i].x+buttons_saves[i].w,(GXColor)DARK_GREY);
      sprintf(msg,"%d/%02d/%02d",slots[i].day,slots[i].month,slots[i].year);
      FONT_alignRight(msg,12,buttons_saves[i].x+buttons_saves[i].w-16,buttons_saves[i].y+(buttons_saves[i].h-28)/2+12,(GXColor)DARK_GREY);
      sprintf(msg,"%02d:%02d",slots[i].hour,slots[i].min);
      FONT_alignRight(msg,12,buttons_saves[i].x+buttons_saves[i].w-16,buttons_saves[i].y+(buttons_saves[i].h-28)/2+28,(GXColor)DARK_GREY);
    }
    else
    {
      FONT_write("Empty Slot",16,buttons_saves[i].x+16,buttons_saves[i].y+(buttons_saves[i].h-16)/2+16,buttons_saves[i].x+buttons_saves[i].h,(GXColor)DARK_GREY);
    }

    if (i == config.s_default)
      gxDrawTexture(star,22,buttons_saves[i].y+(buttons_saves[i].h-star->height)/2,star->width,star->height,255);
  }
  gxTextureClose(&star);
}