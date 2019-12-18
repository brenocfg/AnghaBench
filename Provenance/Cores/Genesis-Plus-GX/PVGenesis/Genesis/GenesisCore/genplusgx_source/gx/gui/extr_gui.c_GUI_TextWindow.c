#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_16__ {int width; int height; } ;
typedef  TYPE_3__ gx_texture ;
struct TYPE_17__ {TYPE_1__** helpers; } ;
typedef  TYPE_4__ gui_menu ;
struct TYPE_15__ {int x; int y; int /*<<< orphan*/  angle; scalar_t__ valid; } ;
struct TYPE_18__ {scalar_t__ keys; TYPE_2__ ir; } ;
struct TYPE_14__ {int* data; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_writeCenter (char*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Frame_s1_png ; 
 int /*<<< orphan*/  Frame_s1_title_png ; 
 int /*<<< orphan*/  GUI_DeleteMenu (TYPE_4__*) ; 
 int /*<<< orphan*/  GUI_DrawMenu (TYPE_4__*) ; 
 int /*<<< orphan*/  GUI_FadeOut () ; 
 int /*<<< orphan*/  SYS_POWEROFF ; 
 int /*<<< orphan*/  SYS_ResetSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Shutdown ; 
 scalar_t__ WHITE ; 
 int /*<<< orphan*/  gxDrawTexture (TYPE_3__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  gxDrawTextureRotate (TYPE_3__*,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 int /*<<< orphan*/  gxTextureClose (TYPE_3__**) ; 
 TYPE_3__* gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ m_input ; 
 int /*<<< orphan*/  shutdown () ; 
 TYPE_3__* w_pointer ; 

void GUI_TextWindow(gui_menu *parent, char *title, char items[][64], u8 nb_items, u8 fontsize)
{
  int i, quit = 0;

#ifdef HW_RVL
  int x,y;
#endif

  /* initialize window */
  gx_texture *window = gxTextureOpenPNG(Frame_s1_png,0);
  gx_texture *top = gxTextureOpenPNG(Frame_s1_title_png,0);

  /* window position */
  int xwindow = (640 - window->width) /2;
  int ywindow = (480 - window->height)/2;

  /* text position */
  int ypos  = ywindow + top->height + (window->height - top->height - fontsize*nb_items) / 2 + fontsize/2;

  /* disable helper comment */
  const u8 *data = NULL;
  if (parent->helpers[1])
  {
    data = parent->helpers[1]->data;
    parent->helpers[1]->data = NULL;
  }

  /* slide in */
  int yoffset = ywindow + window->height;
  while (yoffset > 0)
  {
    /* draw parent menu */
    GUI_DrawMenu(parent);

    /* draw window */
    gxDrawTexture(window,xwindow,ywindow-yoffset,window->width,window->height,230);
    gxDrawTexture(top,xwindow,ywindow-yoffset,top->width,top->height,255);

    /* draw title */
    FONT_writeCenter(title,20,xwindow,xwindow+window->width,ywindow+(top->height-20)/2+20-yoffset,(GXColor)WHITE);

    /* draw  text */
    for (i=0; i<nb_items; i++)
      FONT_writeCenter(items[i],fontsize,xwindow,xwindow+window->width,ypos+i*fontsize-yoffset,(GXColor)WHITE);

    /* update display */
    gxSetScreen();

    /* slide speed */
    yoffset -= 60;
  }

  /* draw menu + text window */
  while (quit == 0)
  {
    /* draw parent menu */
    GUI_DrawMenu(parent);

    /* draw window */
    gxDrawTexture(window,xwindow,ywindow,window->width,window->height,230);
    gxDrawTexture(top,xwindow,ywindow,top->width,top->height,255);

    /* draw title */
    FONT_writeCenter(title,20,xwindow,xwindow+window->width,ywindow+(top->height-20)/2+20,(GXColor)WHITE);

    /* draw text */
    for (i=0; i<nb_items; i++)
    {
      FONT_writeCenter(items[i],fontsize,xwindow,xwindow+window->width,ypos+i*fontsize,(GXColor)WHITE);
    }

#ifdef HW_RVL
    if (Shutdown)
    {
      gxTextureClose(&window);
      gxTextureClose(&top);
      gxTextureClose(&w_pointer);
      GUI_DeleteMenu(parent);
      GUI_FadeOut();
      shutdown();
      SYS_ResetSystem(SYS_POWEROFF, 0, 0);
    }
    else if (m_input.ir.valid)
    {
      /* get cursor position */
      x = m_input.ir.x;
      y = m_input.ir.y;

      /* draw wiimote pointer */
      gxDrawTextureRotate(w_pointer, x-w_pointer->width/2, y-w_pointer->height/2, w_pointer->width, w_pointer->height,m_input.ir.angle,255);
    }
#endif

    /* update screen */
    gxSetScreen();

    /* wait for exit buttons */
    if (m_input.keys)
      quit = 1;
  }

  /* reset initial vertical offset */

  /* slide out */
  yoffset = 0;
  while (yoffset < (ywindow + window->height))
  {
    /* draw parent menu */
    GUI_DrawMenu(parent);

    /* draw window */
    gxDrawTexture(window,xwindow,ywindow-yoffset,window->width,window->height,230);
    gxDrawTexture(top,xwindow,ywindow-yoffset,top->width,top->height,255);

    /* draw title */
    FONT_writeCenter(title,20,xwindow,xwindow+window->width,ywindow+(top->height-20)/2+20-yoffset,(GXColor)WHITE);

    /* draw  text */
    for (i=0; i<nb_items; i++)
      FONT_writeCenter(items[i],fontsize,xwindow,xwindow+window->width,ypos+i*fontsize-yoffset,(GXColor)WHITE);

    /* update display */
    gxSetScreen();

    /* slide speed */
    yoffset += 60;
  }

  /* restore helper comment */
  if (parent->helpers[1])
    parent->helpers[1]->data = data;

  /* final position */
  GUI_DrawMenu(parent);
  gxSetScreen();

  /* close textures */
  gxTextureClose(&window);
  gxTextureClose(&top);
}