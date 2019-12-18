#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct au1200_lcd_window_regs_t {int xpos; int ypos; int alpha_color; int alpha_mode; int priority; int channel; int buffer_format; int color_order; int pixel_order; int xsize; int ysize; int colorkey_mode; int double_buffer_mode; int ram_array_mode; unsigned int enable; } ;
struct TYPE_4__ {unsigned int winenable; TYPE_1__* window; } ;
struct TYPE_3__ {int winctrl0; int winctrl1; int winctrl2; } ;

/* Variables and functions */
 int LCD_WINCTRL0_A ; 
 int LCD_WINCTRL0_AEN ; 
 int LCD_WINCTRL0_OX ; 
 int LCD_WINCTRL0_OY ; 
 int LCD_WINCTRL1_CCO ; 
 int LCD_WINCTRL1_FRM ; 
 int LCD_WINCTRL1_PIPE ; 
 int LCD_WINCTRL1_PO ; 
 int LCD_WINCTRL1_PRI ; 
 int LCD_WINCTRL1_SZX ; 
 int LCD_WINCTRL1_SZY ; 
 int LCD_WINCTRL2_CKMODE ; 
 int LCD_WINCTRL2_DBM ; 
 int LCD_WINCTRL2_RAM ; 
 int /*<<< orphan*/  au_sync () ; 
 TYPE_2__* lcd ; 

__attribute__((used)) static void get_window(unsigned int plane,
	struct au1200_lcd_window_regs_t *pdata)
{
	/* Window control register 0 */
	pdata->xpos = (lcd->window[plane].winctrl0 & LCD_WINCTRL0_OX) >> 21;
	pdata->ypos = (lcd->window[plane].winctrl0 & LCD_WINCTRL0_OY) >> 10;
	pdata->alpha_color = (lcd->window[plane].winctrl0 & LCD_WINCTRL0_A) >> 2;
	pdata->alpha_mode = (lcd->window[plane].winctrl0 & LCD_WINCTRL0_AEN) >> 1;

	/* Window control register 1 */
	pdata->priority = (lcd->window[plane].winctrl1& LCD_WINCTRL1_PRI) >> 30;
	pdata->channel = (lcd->window[plane].winctrl1 & LCD_WINCTRL1_PIPE) >> 29;
	pdata->buffer_format = (lcd->window[plane].winctrl1 & LCD_WINCTRL1_FRM) >> 25;
	pdata->color_order = (lcd->window[plane].winctrl1 & LCD_WINCTRL1_CCO) >> 24;
	pdata->pixel_order = (lcd->window[plane].winctrl1 & LCD_WINCTRL1_PO) >> 22;
	pdata->xsize = ((lcd->window[plane].winctrl1 & LCD_WINCTRL1_SZX) >> 11) + 1;
	pdata->ysize = (lcd->window[plane].winctrl1 & LCD_WINCTRL1_SZY) + 1;

	/* Window control register 2 */
	pdata->colorkey_mode = (lcd->window[plane].winctrl2 & LCD_WINCTRL2_CKMODE) >> 24;
	pdata->double_buffer_mode = (lcd->window[plane].winctrl2 & LCD_WINCTRL2_DBM) >> 23;
	pdata->ram_array_mode = (lcd->window[plane].winctrl2 & LCD_WINCTRL2_RAM) >> 21;

	pdata->enable = (lcd->winenable >> plane) & 1;
	au_sync();
}