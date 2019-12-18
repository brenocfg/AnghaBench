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
struct TYPE_7__ {scalar_t__ refresh; TYPE_3__* window; TYPE_3__* top; TYPE_5__* parent; void* throbber; } ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_writeCenter (char*,int,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Frame_s2_png ; 
 int /*<<< orphan*/  Frame_s2_title_png ; 
 int /*<<< orphan*/  Frame_throbber_png ; 
 int /*<<< orphan*/  GUI_DrawMenu (TYPE_5__*) ; 
 int /*<<< orphan*/  GUI_MsgBoxUpdate (char*,char*) ; 
 int /*<<< orphan*/  LWP_CreateThread (int /*<<< orphan*/ *,void*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MsgBox_Thread ; 
 scalar_t__ SILENT ; 
 scalar_t__ TRUE ; 
 scalar_t__ WHITE ; 
 int /*<<< orphan*/  bg_color ; 
 int /*<<< orphan*/  gxClearScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gxDrawTexture (TYPE_3__*,int,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 void* gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ message_box ; 
 int /*<<< orphan*/  msgboxthread ; 

void GUI_MsgBoxOpen(char *title, char *msg, bool throbber)
{
  if (SILENT)
    return;

  /* update text */
  GUI_MsgBoxUpdate(title,msg);

  /* ensure we are not already running */
  if (!message_box.refresh)
  {
    /* initialize default textures */
    message_box.window = gxTextureOpenPNG(Frame_s2_png,0);
    message_box.top = gxTextureOpenPNG(Frame_s2_title_png,0);
    if (throbber)
      message_box.throbber = gxTextureOpenPNG(Frame_throbber_png,0);

    /* window position */
    int xwindow = 166;
    int ywindow = 160;
    int ypos = 248;

    /* disable helper comments */
    if (message_box.parent)
    {
      if (message_box.parent->helpers[0])
        message_box.parent->helpers[0]->data = 0;
      if (message_box.parent->helpers[1])
        message_box.parent->helpers[1]->data = 0;
    }

    /* slide in */
    int yoffset = ywindow + message_box.window->height;
    while (yoffset > 0)
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
      if (title)
        FONT_writeCenter(title,20,xwindow,xwindow+message_box.window->width,ywindow+(message_box.top->height-20)/2+20-yoffset,(GXColor)WHITE);

      /* draw box message */
      if (msg)
        FONT_writeCenter(msg,18,xwindow,xwindow+message_box.window->width,ypos-yoffset,(GXColor)WHITE);

      /* update display */
      gxSetScreen();

      /* slide speed */
      yoffset -= 60;
    }

    /* create LWP thread for MessageBox refresh */
    message_box.refresh = TRUE;
    LWP_CreateThread (&msgboxthread, (void *)MsgBox_Thread, &message_box, NULL, 0, 70);
  }
}