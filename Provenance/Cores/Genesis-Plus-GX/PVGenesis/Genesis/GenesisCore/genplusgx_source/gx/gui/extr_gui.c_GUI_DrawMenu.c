#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int max_images; int max_buttons; int offset; int selected; int /*<<< orphan*/  (* cb ) () ;TYPE_3__** helpers; TYPE_5__** arrows; TYPE_3__* items; TYPE_5__* buttons; int /*<<< orphan*/  title; TYPE_4__* bg_images; scalar_t__ screenshot; } ;
typedef  TYPE_2__ gui_menu ;
struct TYPE_9__ {int x; int y; int w; int h; int /*<<< orphan*/  comment; scalar_t__ texture; scalar_t__ data; int /*<<< orphan*/  text; } ;
typedef  TYPE_3__ gui_item ;
struct TYPE_10__ {int state; int x; int y; int w; int h; int alpha; scalar_t__ texture; } ;
typedef  TYPE_4__ gui_image ;
struct TYPE_11__ {int state; int x; int y; int w; int h; TYPE_1__* data; } ;
typedef  TYPE_5__ gui_butn ;
struct TYPE_7__ {scalar_t__* texture; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 int BUTTON_SELECTED ; 
 int BUTTON_VISIBLE ; 
 scalar_t__ DARK_GREY ; 
 int /*<<< orphan*/  FONT_alignRight (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FONT_write (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FONT_writeCenter (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int IMAGE_REPEAT ; 
 int IMAGE_VISIBLE ; 
 scalar_t__ WHITE ; 
 int /*<<< orphan*/  bg_color ; 
 int /*<<< orphan*/  gxClearScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxDrawScreenshot (scalar_t__) ; 
 int /*<<< orphan*/  gxDrawTexture (scalar_t__,int,int,int,int,int) ; 
 int /*<<< orphan*/  gxDrawTextureRepeat (scalar_t__,int,int,int,int,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

void GUI_DrawMenu(gui_menu *menu)
{
  int i;
  gui_item *item;
  gui_butn *button;
  gui_image *image;

  /* background color */
  if (menu->screenshot)
  {
    gxClearScreen((GXColor)BLACK);
    gxDrawScreenshot(menu->screenshot);
  }
  else
  {
    gxClearScreen(bg_color);
  }

  /* background elements */
  for (i=0; i<menu->max_images; i++)
  {
    image = &menu->bg_images[i];
    if (image->state & IMAGE_VISIBLE)
    {
      if (image->state & IMAGE_REPEAT)
        gxDrawTextureRepeat(image->texture,image->x,image->y,image->w,image->h,image->alpha);
      else 
        gxDrawTexture(image->texture,image->x,image->y,image->w,image->h,image->alpha);
    }
  }

  /* menu title */
  FONT_write(menu->title, 22,10,56,640,(GXColor)WHITE);

  /* draw buttons + items */
  for (i=0; i<menu->max_buttons; i++)
  {
    button = &menu->buttons[i];

    if (button->state & BUTTON_VISIBLE)
    {
      /* item select (text or image) */
      item = (menu->items) ? (&menu->items[menu->offset + i]) : NULL;
      
      /* draw button + items */ 
      if ((i == menu->selected) || (button->state & BUTTON_SELECTED))
      {
        if (button->data)
          gxDrawTexture(button->data->texture[1],button->x-4,button->y-4,button->w+8,button->h+8,255);

        if (item)
        {
          if (item->texture)
          {
            gxDrawTexture(item->texture, item->x-4,item->y-4,item->w+8,item->h+8,255);
            FONT_writeCenter(item->text,18,button->x+4,item->x-4,button->y+(button->h - 36)/2+18,(GXColor)DARK_GREY);
          }
          else
          {
            FONT_writeCenter(item->text,18,item->x-4,item->x+item->w+4,button->y+(button->h-18)/2+18,(GXColor)DARK_GREY);
          }
        }
      }
      else
      {
        if (button->data)
          gxDrawTexture(button->data->texture[0],button->x,button->y,button->w, button->h,255);

        if (item)
        {
          if (item->texture)
          {
            gxDrawTexture(item->texture,item->x,item->y,item->w,item->h,255);
            FONT_writeCenter(item->text,16,button->x+8,item->x,button->y+(button->h - 32)/2+16,(GXColor)DARK_GREY);
          }
          else
          {
            FONT_writeCenter(item->text,16,item->x,item->x+item->w,button->y+(button->h - 16)/2+16,(GXColor)DARK_GREY);
          }
        }
      }
    }
  }

  /* draw arrow */
  for (i=0; i<2; i++)
  {
    button = menu->arrows[i];
    if (button)
    {
      if (button->state & BUTTON_VISIBLE)
      {
        if (menu->selected == (menu->max_buttons + i))
          gxDrawTexture(button->data->texture[1],button->x-2,button->y-2,button->w+4,button->h+4,255);
        else
          gxDrawTexture(button->data->texture[0],button->x,button->y,button->w, button->h,255);
      }
    }
  }

  /* left comment */
  item = menu->helpers[0];
  if (item)
  {
    if (item->data && strlen(item->comment))
    {
      gxDrawTexture(item->texture,item->x,item->y,item->w,item->h,255);
      FONT_write(item->comment,16,item->x+item->w+6,item->y+(item->h-16)/2 + 16,640,(GXColor)WHITE);
    }
  }

  /* right comment */
  item = menu->helpers[1];
  if (item)
  {
    if (item->data && strlen(item->comment))
    {
      gxDrawTexture(item->texture,item->x,item->y,item->w,item->h,255);
      FONT_alignRight(item->comment,16,item->x-6,item->y+(item->h-16)/2+16,(GXColor)WHITE);
    }
  }

  if (menu->cb)
    menu->cb();
}