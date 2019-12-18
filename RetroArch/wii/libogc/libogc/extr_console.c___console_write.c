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
struct _reent {int dummy; } ;
struct TYPE_3__ {scalar_t__ cursor_row; int cursor_col; int con_cols; scalar_t__ con_rows; int con_stride; int con_yres; int /*<<< orphan*/  background; scalar_t__ destbuffer; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 int FONT_YFACTOR ; 
 int FONT_YGAP ; 
 int FONT_YSIZE ; 
 int TAB_SIZE ; 
 int /*<<< orphan*/  __console_drawc (char) ; 
 int __console_parse_escsequence (char*) ; 
 scalar_t__ __gecko_safe ; 
 scalar_t__ __gecko_status ; 
 TYPE_1__* curr_con ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_sendbuffer (scalar_t__,char const*,size_t) ; 
 int /*<<< orphan*/  usb_sendbuffer_safe (scalar_t__,char const*,size_t) ; 

int __console_write(struct _reent *r,void *fd,const char *ptr,size_t len)
{
	size_t i = 0;
	char *tmp = (char*)ptr;
	console_data_s *con;
	char chr;

	if(__gecko_status>=0) {
		if(__gecko_safe)
			usb_sendbuffer_safe(__gecko_status,ptr,len);
		else
			usb_sendbuffer(__gecko_status,ptr,len);
	}

	if(!curr_con) return -1;
	con = curr_con;
	if(!tmp || len<=0) return -1;

	i = 0;
	while(*tmp!='\0' && i<len)
	{
		chr = *tmp++;
		i++;
		if ( (chr == 0x1b) && (*tmp == '[') )
		{
			/* escape sequence found */
			int k;

			tmp++;
			i++;
			k = __console_parse_escsequence(tmp);
			tmp += k;
			i += k;
		}
		else
		{
			switch(chr)
			{
				case '\n':
					con->cursor_row++;
					con->cursor_col = 0;
					break;
				case '\r':
					con->cursor_col = 0;
					break;
				case '\b':
					con->cursor_col--;
					if(con->cursor_col < 0)
					{
						con->cursor_col = 0;
					}
					break;
				case '\f':
					con->cursor_row++;
					break;
				case '\t':
					if(con->cursor_col%TAB_SIZE) con->cursor_col += (con->cursor_col%TAB_SIZE);
					else con->cursor_col += TAB_SIZE;
					break;
				default:
					__console_drawc(chr);
					con->cursor_col++;

					if( con->cursor_col >= con->con_cols)
					{
						/* if right border reached wrap around */
						con->cursor_row++;
						con->cursor_col = 0;
					}
			}
		}

		if( con->cursor_row >= con->con_rows)
		{
			/* if bottom border reached scroll */
			memcpy(con->destbuffer,
				con->destbuffer+con->con_stride*(FONT_YSIZE*FONT_YFACTOR+FONT_YGAP),
				con->con_stride*con->con_yres-FONT_YSIZE);

			unsigned int cnt = (con->con_stride * (FONT_YSIZE * FONT_YFACTOR + FONT_YGAP))/4;
			unsigned int *ptr = (unsigned int*)(con->destbuffer + con->con_stride * (con->con_yres - FONT_YSIZE));
			while(cnt--)
				*ptr++ = con->background;
			con->cursor_row--;
		}
	}

	return i;
}