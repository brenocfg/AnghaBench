#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_14__ {int selected; int max_items; int max_buttons; int offset; TYPE_5__* buttons; TYPE_1__** helpers; TYPE_4__* items; TYPE_5__** arrows; } ;
typedef  TYPE_3__ gui_menu ;
struct TYPE_15__ {char* comment; } ;
typedef  TYPE_4__ gui_item ;
struct TYPE_16__ {int state; int x; int w; int y; int h; scalar_t__* shift; } ;
typedef  TYPE_5__ gui_butn ;
struct TYPE_19__ {scalar_t__ sfx_volume; } ;
struct TYPE_13__ {int x; int y; int /*<<< orphan*/  angle; scalar_t__ valid; } ;
struct TYPE_18__ {int keys; TYPE_2__ ir; } ;
struct TYPE_17__ {int width; int height; } ;
struct TYPE_12__ {int /*<<< orphan*/  comment; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASND_GetFirstUnusedVoice () ; 
 int /*<<< orphan*/  ASND_SetVoice (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int BUTTON_ACTIVE ; 
 int BUTTON_OVER_SFX ; 
 int BUTTON_SELECT_SFX ; 
 int BUTTON_VISIBLE ; 
 int /*<<< orphan*/  GUI_DeleteMenu (TYPE_3__*) ; 
 int /*<<< orphan*/  GUI_FadeOut () ; 
 int PAD_BUTTON_A ; 
 int PAD_BUTTON_B ; 
 int PAD_BUTTON_DOWN ; 
 int PAD_BUTTON_LEFT ; 
 int PAD_BUTTON_RIGHT ; 
 int PAD_BUTTON_UP ; 
 int PAD_TRIGGER_Z ; 
 int /*<<< orphan*/  SYS_POWEROFF ; 
 int /*<<< orphan*/  SYS_ResetSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Shutdown ; 
 int /*<<< orphan*/  VOICE_MONO_16BIT ; 
 scalar_t__ button_over_pcm ; 
 int /*<<< orphan*/  button_over_pcm_size ; 
 scalar_t__ button_select_pcm ; 
 int /*<<< orphan*/  button_select_pcm_size ; 
 TYPE_9__ config ; 
 int /*<<< orphan*/  gxDrawTextureRotate (TYPE_6__*,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 TYPE_7__ m_input ; 
 int /*<<< orphan*/  shutdown () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 TYPE_6__* w_pointer ; 

int GUI_UpdateMenu(gui_menu *menu)
{
  u16 p;
  int ret = 0;
  int selected = menu->selected;
  int max_items = menu->max_items;
  int max_buttons = menu->max_buttons;
  gui_butn *button;

#ifdef HW_RVL
  if (Shutdown)
  {
    GUI_DeleteMenu(menu);
    GUI_FadeOut();
    shutdown();
    SYS_ResetSystem(SYS_POWEROFF, 0, 0);
  }
  else if (m_input.ir.valid)
  {
    /* get cursor position */
    int x = m_input.ir.x;
    int y = m_input.ir.y;

    /* draw wiimote pointer */
    gxDrawTextureRotate(w_pointer, x-w_pointer->width/2, y-w_pointer->height/2, w_pointer->width, w_pointer->height,m_input.ir.angle,255);

    /* check for valid buttons */
    selected = max_buttons + 2;
    int i;
    for (i=0; i<max_buttons; i++)
    {
      button = &menu->buttons[i];
      if ((button->state & BUTTON_ACTIVE) && (button->state & BUTTON_VISIBLE))
      {
        if((x>=button->x)&&(x<=(button->x+button->w))&&(y>=button->y)&&(y<=(button->y+button->h)))
        {
          selected = i;
          break;
        }
      }
    }

    for (i=0; i<2; i++)
    {
      button = menu->arrows[i];
      if (button)
      {
        if ((button->state & BUTTON_ACTIVE) && (button->state & BUTTON_VISIBLE))
        {
          if ((x<=(button->x+button->w))&&(y>=button->y)&&(y<=(button->y+button->h)))
          {
            selected = max_buttons + i;
            break;
          }
        }
      }
    }
  }
  else
  {
    /* reinitialize selection */
    if (selected >= menu->max_buttons)
    {
      selected = 0;
      while ((selected < (menu->max_buttons + 2)) && 
             (!(menu->buttons[selected].state & BUTTON_ACTIVE) || 
              !(menu->buttons[selected].state & BUTTON_VISIBLE)))
        selected++;
    }
  }
#endif

  /* update screen */
  gxSetScreen();

  /* update menu */
  p = m_input.keys;

  if (selected < max_buttons)
  {
    button = &menu->buttons[selected];
    if (p & PAD_BUTTON_UP)
    {
      selected -= button->shift[0];
      if (selected < 0)
      {
        selected = 0;
        if (menu->offset)
          menu->offset --;
      }
    }
    else if (p & PAD_BUTTON_DOWN)
    {
      selected += button->shift[1];
      if (selected >= max_buttons)
      {
        selected = max_buttons - 1;
        if ((menu->offset + selected) < (max_items - 1))
          menu->offset ++;
      }
    }
    else if (p & PAD_BUTTON_LEFT)
    {
      selected -= button->shift[2];
      if (selected < 0)
      {
        selected = 0;
        if (menu->offset)
          menu->offset --;
      }
    }
    else if (p & PAD_BUTTON_RIGHT)
    {
      selected += button->shift[3];
      if (selected >= max_buttons)
      {
        selected = max_buttons - 1;
        if ((menu->offset + selected) < (max_items - 1))
          menu->offset ++;
      }
    }
  }

  if (p & PAD_BUTTON_A)
  {
    if (selected < max_buttons)
      ret = 1; /* menu clicked */
    else if (selected == max_buttons)
      menu->offset --; /* up arrow */
    else if (selected == (max_buttons+1))
      menu->offset ++; /* down arrow */
  }
  else if ((p & PAD_BUTTON_B) || (p & PAD_TRIGGER_Z))
  {
    /* quit menu */
    ret = -1;
  }

  /* selected item has changed ? */
  if (menu->selected != selected)
  {
    if (selected < max_buttons)
    {
      /* sound fx */
      button = &menu->buttons[selected];
      if (button->state & BUTTON_OVER_SFX)
      {
        ASND_SetVoice(ASND_GetFirstUnusedVoice(),VOICE_MONO_16BIT,22050,0,(u8 *)button_over_pcm,button_over_pcm_size,
                      ((int)config.sfx_volume * 255) / 100,((int)config.sfx_volume * 255) / 100,NULL);
      }
    }
    else if (selected < (max_buttons + 2))
    {
      /* sound fx */
      button = menu->arrows[selected-max_buttons];
      if (button->state & BUTTON_OVER_SFX)
      {
        ASND_SetVoice(ASND_GetFirstUnusedVoice(),VOICE_MONO_16BIT,22050,0,(u8 *)button_over_pcm,button_over_pcm_size,
                      ((int)config.sfx_volume * 255) / 100,((int)config.sfx_volume * 255) / 100,NULL);
      }
    }

    /* update selection */
    menu->selected = selected;
  }

  /* update helper comment */
  if (menu->helpers[1])
  {
    if ((menu->offset + selected) < max_items)
    {
      gui_item *item = &menu->items[menu->offset + selected];
      strcpy(menu->helpers[1]->comment,item->comment);
    }
    else
    {
      strcpy(menu->helpers[1]->comment,"");
    }
  }

  if (ret > 0)
  {
    if (selected < max_buttons)
    {
      /* sound fx */
      button = &menu->buttons[selected];
      if (button->state & BUTTON_SELECT_SFX)
      {
        ASND_SetVoice(ASND_GetFirstUnusedVoice(),VOICE_MONO_16BIT,22050,0,(u8 *)button_select_pcm,button_select_pcm_size,
                      ((int)config.sfx_volume * 255) / 100,((int)config.sfx_volume * 255) / 100,NULL);
      }
    }
  }

  return ret;
}