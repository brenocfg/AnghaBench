#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {char* title; int selected; int max_buttons; TYPE_3__** arrows; TYPE_3__* buttons; } ;
typedef  TYPE_2__ gui_menu ;
struct TYPE_11__ {int state; int x; int w; int y; int h; } ;
typedef  TYPE_3__ gui_butn ;
struct TYPE_9__ {int x; int y; int /*<<< orphan*/  angle; scalar_t__ valid; } ;
struct TYPE_13__ {TYPE_1__ ir; } ;
struct TYPE_12__ {int width; int height; } ;

/* Variables and functions */
 int BUTTON_ACTIVE ; 
 int BUTTON_VISIBLE ; 
 int /*<<< orphan*/  GUI_DrawMenu (TYPE_2__*) ; 
 int /*<<< orphan*/  gxDrawTextureRotate (TYPE_4__*,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 TYPE_5__ m_input ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 TYPE_4__* w_pointer ; 

void GUI_SlideMenuTitle(gui_menu *m, int title_offset)
{
#ifdef HW_RVL
  gui_butn *button;
  int i,x,y;
#endif

  char title[64];
  strcpy(title,m->title);

  while (title_offset > 0)
  {
    /* update title */
    strcpy(m->title,title+title_offset);
    m->title[strlen(title)-title_offset-1] = 0;

    /* draw menu */
    GUI_DrawMenu(m);

#ifdef HW_RVL
    /* keep pointer active */
    if (m_input.ir.valid)
    {
      /* get cursor position */
      x = m_input.ir.x;
      y = m_input.ir.y;

      /* draw wiimote pointer */
      gxDrawTextureRotate(w_pointer, x-w_pointer->width/2, y-w_pointer->height/2, w_pointer->width, w_pointer->height,m_input.ir.angle,255);

      /* check for valid buttons */
      m->selected = m->max_buttons + 2;
      for (i=0; i<m->max_buttons; i++)
      {
        button = &m->buttons[i];
        if ((button->state & BUTTON_ACTIVE)&&(x>=button->x)&&(x<=(button->x+button->w))&&(y>=button->y)&&(y<=(button->y+button->h)))
        {
          m->selected = i;
          break;
        }
      }

      for (i=0; i<2; i++)
      {
        button = m->arrows[i];
        if (button)
        {
          if (button->state & BUTTON_VISIBLE)
          {
            if ((x<=(button->x+button->w))&&(y>=button->y)&&(y<=(button->y+button->h)))
            {
              m->selected = m->max_buttons + i;
              break;
            }
          }
        }
      }
    }
#endif
    gxSetScreen();
    usleep(6000);
    title_offset--;
  }
  strcpy(m->title,title);
}