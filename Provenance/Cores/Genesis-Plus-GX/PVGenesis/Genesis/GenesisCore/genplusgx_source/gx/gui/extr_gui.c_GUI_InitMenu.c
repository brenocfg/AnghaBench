#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int max_images; scalar_t__ offset; int max_buttons; int max_items; TYPE_3__* items; TYPE_5__* buttons; TYPE_5__** arrows; TYPE_3__** helpers; TYPE_4__* bg_images; } ;
typedef  TYPE_2__ gui_menu ;
struct TYPE_10__ {scalar_t__ data; void* texture; } ;
typedef  TYPE_3__ gui_item ;
struct TYPE_11__ {scalar_t__ data; void* texture; } ;
typedef  TYPE_4__ gui_image ;
struct TYPE_12__ {TYPE_1__* data; int /*<<< orphan*/  state; } ;
typedef  TYPE_5__ gui_butn ;
struct TYPE_13__ {TYPE_2__* parent; } ;
struct TYPE_8__ {scalar_t__* image; void** texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON_VISIBLE ; 
 void* gxTextureOpenPNG (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_6__ message_box ; 

void GUI_InitMenu(gui_menu *menu)
{
  int i;
  gui_item *item;
  gui_butn *button;
  gui_image *image;

  /* background elements */
  for (i=0; i<menu->max_images; i++)
  {
    image = &menu->bg_images[i];
    image->texture = gxTextureOpenPNG(image->data,0);
  }

  for (i=0; i<2; i++)
  {
    /* key helpers */
    item = menu->helpers[i];
    if (item)
      item->texture = gxTextureOpenPNG(item->data,0);

    /* arrows */
    button = menu->arrows[i];
    if (button)
    {
      if (!button->data->texture[0])
        button->data->texture[0] = gxTextureOpenPNG(button->data->image[0],0);
      if (!button->data->texture[1])
        button->data->texture[1] = gxTextureOpenPNG(button->data->image[1],0);

      /* initial state */
      button->state &= ~BUTTON_VISIBLE;
      if (((i==0) && (menu->offset != 0)) || ((i==1) && (menu->offset + menu->max_buttons) < menu->max_items))
        button->state |= BUTTON_VISIBLE;
    }
  }

  /* menu buttons */
  for (i=0; i<menu->max_buttons; i++)
  {
    button = &menu->buttons[i];
    if (button->data)
    {
      if (!button->data->texture[0])
        button->data->texture[0] = gxTextureOpenPNG(button->data->image[0],0);
      if (!button->data->texture[1])
        button->data->texture[1] = gxTextureOpenPNG(button->data->image[1],0);
    }
  }

  /* menu items */
  for (i=0; i<menu->max_items; i++)
  {
    item = &menu->items[i];
    if (item->data)
      item->texture = gxTextureOpenPNG(item->data,0);
  }

  /* update message box */
  message_box.parent = menu;
}