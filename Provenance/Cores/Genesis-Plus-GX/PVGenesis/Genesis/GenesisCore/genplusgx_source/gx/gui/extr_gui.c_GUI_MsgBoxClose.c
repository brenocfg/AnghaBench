#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__** helpers; } ;
struct TYPE_8__ {int height; scalar_t__ width; } ;
struct TYPE_7__ {TYPE_3__* throbber; TYPE_3__* buttonA; TYPE_3__* top; TYPE_3__* window; TYPE_5__* parent; scalar_t__ msg; scalar_t__ title; scalar_t__ refresh; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FONT_writeCenter (scalar_t__,int,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUI_DrawMenu (TYPE_5__*) ; 
 int /*<<< orphan*/  Key_A_png ; 
 int /*<<< orphan*/  Key_B_png ; 
 int /*<<< orphan*/  LWP_JoinThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ WHITE ; 
 int /*<<< orphan*/  bg_color ; 
 int /*<<< orphan*/  gxClearScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxDrawTexture (TYPE_3__*,int,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 int /*<<< orphan*/  gxTextureClose (TYPE_3__**) ; 
 TYPE_2__ message_box ; 
 int /*<<< orphan*/  msgboxthread ; 

void GUI_MsgBoxClose(void)
{
  if (message_box.refresh)
  {
    /* suspend MessageBox refresh */
    message_box.refresh = FALSE;
    LWP_JoinThread(msgboxthread, NULL);

    /* window position */
    int xwindow = 166;
    int ywindow = 160;
    int ypos = 248;

    /* slide out */
    int yoffset = 0;
    while (yoffset < (ywindow + message_box.window->height))
    {
      /* draw parent menu */
      if (message_box.parent)
      {
        GUI_DrawMenu(message_box.parent);
      }
      else
      {
        gxClearScreen(bg_color);
      }

      /* draw window */
      gxDrawTexture(message_box.window,xwindow,ywindow-yoffset,message_box.window->width,message_box.window->height,230);
      gxDrawTexture(message_box.top,xwindow,ywindow-yoffset,message_box.top->width,message_box.top->height,255);

      /* draw title */
      if (message_box.title)
        FONT_writeCenter(message_box.title,20,xwindow,xwindow+message_box.window->width,ywindow+(message_box.top->height-20)/2+20-yoffset,(GXColor)WHITE);

      /* draw text */
      if (message_box.msg)
        FONT_writeCenter(message_box.msg,18,xwindow,xwindow+message_box.window->width,ypos-yoffset,(GXColor)WHITE);

      /* update display */
      gxSetScreen();

      /* slide speed */
      yoffset += 60;
    }

    if (message_box.parent)
    {
      /* restore helper comment */
      if (message_box.parent->helpers[0])
        message_box.parent->helpers[0]->data = Key_B_png;
      if (message_box.parent->helpers[1])
        message_box.parent->helpers[1]->data = Key_A_png;
    
      /* final position */
      GUI_DrawMenu(message_box.parent);
    }
    else
    {
      gxClearScreen(bg_color);
    }
    
    gxSetScreen();

    /* clear all textures */
    gxTextureClose(&message_box.window);
    gxTextureClose(&message_box.top);
    gxTextureClose(&message_box.buttonA);
    gxTextureClose(&message_box.throbber);
  }
}