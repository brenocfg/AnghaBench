#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int con_stride; int cursor_row; int cursor_col; unsigned char* font; unsigned int foreground; unsigned int background; scalar_t__ destbuffer; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 int FONT_XSIZE ; 
 int FONT_YSIZE ; 
 scalar_t__ TRUE ; 
 TYPE_1__* curr_con ; 
 scalar_t__ do_xfb_copy ; 

__attribute__((used)) static void __console_drawc(int c)
{
	console_data_s *con;
	int ay;
	unsigned int *ptr;
	unsigned char *pbits;
	unsigned char bits;
	unsigned int color;
	unsigned int fgcolor, bgcolor;
	unsigned int nextline;

	if(do_xfb_copy==TRUE) return;
	if(!curr_con) return;
	con = curr_con;

	ptr = (unsigned int*)(con->destbuffer + ( con->con_stride *  con->cursor_row * FONT_YSIZE ) + ((con->cursor_col * FONT_XSIZE / 2) * 4));
	pbits = &con->font[c * FONT_YSIZE];
	nextline = con->con_stride/4 - 4;
	fgcolor = con->foreground;
	bgcolor = con->background;

	for (ay = 0; ay < FONT_YSIZE; ay++)
	{
		/* hard coded loop unrolling ! */
		/* this depends on FONT_XSIZE = 8*/
#if FONT_XSIZE == 8
		bits = *pbits++;

		/* bits 1 & 2 */
		if ( bits & 0x80)
			color = fgcolor & 0xFFFF00FF;
		else
			color = bgcolor & 0xFFFF00FF;
		if (bits & 0x40)
			color |= fgcolor  & 0x0000FF00;
		else
			color |= bgcolor  & 0x0000FF00;
		*ptr++ = color;

		/* bits 3 & 4 */
		if ( bits & 0x20)
			color = fgcolor & 0xFFFF00FF;
		else
			color = bgcolor & 0xFFFF00FF;
		if (bits & 0x10)
			color |= fgcolor  & 0x0000FF00;
		else
			color |= bgcolor  & 0x0000FF00;
		*ptr++ = color;

		/* bits 5 & 6 */
		if ( bits & 0x08)
			color = fgcolor & 0xFFFF00FF;
		else
			color = bgcolor & 0xFFFF00FF;
		if (bits & 0x04)
			color |= fgcolor  & 0x0000FF00;
		else
			color |= bgcolor  & 0x0000FF00;
		*ptr++ = color;

		/* bits 7 & 8 */
		if ( bits & 0x02)
			color = fgcolor & 0xFFFF00FF;
		else
			color = bgcolor & 0xFFFF00FF;
		if (bits & 0x01)
			color |= fgcolor  & 0x0000FF00;
		else
			color |= bgcolor  & 0x0000FF00;
		*ptr++ = color;

		/* next line */
		ptr += nextline;
#endif
	}
}