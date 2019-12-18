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
struct TYPE_8__ {int max_images; int max_buttons; int max_items; TYPE_3__* items; TYPE_5__* buttons; TYPE_5__** arrows; TYPE_3__** helpers; TYPE_4__* bg_images; } ;
typedef  TYPE_2__ gui_menu ;
struct TYPE_9__ {int /*<<< orphan*/  texture; } ;
typedef  TYPE_3__ gui_item ;
struct TYPE_10__ {int /*<<< orphan*/  texture; } ;
typedef  TYPE_4__ gui_image ;
struct TYPE_11__ {TYPE_1__* data; } ;
typedef  TYPE_5__ gui_butn ;
struct TYPE_7__ {int /*<<< orphan*/ * texture; } ;

/* Variables and functions */
 int /*<<< orphan*/  gxTextureClose (int /*<<< orphan*/ *) ; 

void GUI_DeleteMenu(gui_menu *menu)
{
  int i;
  gui_butn *button;
  gui_item *item;
  gui_image *image;

  /* background elements */
  for (i=0; i<menu->max_images; i++)
  {
    image = &menu->bg_images[i];
    gxTextureClose(&image->texture);
  }

  for (i=0; i<2; i++)
  {
    /* key helpers */
    item = menu->helpers[i];
    if (item)
      gxTextureClose(&item->texture);

    /* arrows */
    button = menu->arrows[i];
    if (button)
    {
      gxTextureClose(&button->data->texture[0]);
      gxTextureClose(&button->data->texture[1]);
    }
  }

  /* menu buttons */
  for (i=0; i<menu->max_buttons; i++)
  {
    button = &menu->buttons[i];
    if (button->data)
    {
      gxTextureClose(&button->data->texture[0]);
      gxTextureClose(&button->data->texture[1]);
    }
  }

  /* menu items */
  for (i=0; i<menu->max_items; i++)
  {
    item = &menu->items[i];
    gxTextureClose(&item->texture);
  }
}