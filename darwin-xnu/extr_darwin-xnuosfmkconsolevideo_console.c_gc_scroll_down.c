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
typedef  unsigned int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* scroll_down ) (int,unsigned int,unsigned int) ;int /*<<< orphan*/  (* paint_char ) (unsigned int,unsigned int,char,scalar_t__,char,scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__ v_columns; } ;

/* Variables and functions */
 scalar_t__ ATTR_NONE ; 
 int /*<<< orphan*/  COLOR_CODE_GET (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* gc_buffer_attributes ; 
 char* gc_buffer_characters ; 
 unsigned char* gc_buffer_colorcodes ; 
 int gc_buffer_columns ; 
 unsigned int gc_buffer_rows ; 
 int /*<<< orphan*/  gc_buffer_size ; 
 int /*<<< orphan*/  gc_clear_screen (scalar_t__,unsigned int,unsigned int,unsigned int,int) ; 
 unsigned char gc_color_code ; 
 TYPE_2__ gc_ops ; 
 int /*<<< orphan*/  gc_update_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned int,char,scalar_t__,char,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (unsigned int,unsigned int,char,scalar_t__,char,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (unsigned int,unsigned int,char,scalar_t__,char,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (unsigned int,unsigned int,char,scalar_t__,char,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (int,unsigned int,unsigned int) ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void 
gc_scroll_down(int num, unsigned int top, unsigned int bottom)
{
	if (!gc_buffer_size) return;

	if ( bottom <= gc_buffer_rows )
	{
		unsigned char colorcodesave = gc_color_code;
		uint32_t column, row;
		uint32_t index, jump;

		jump = num * gc_buffer_columns;

		for ( row = bottom - 1 ; row >= top + num ; row-- )
		{
			index = row * gc_buffer_columns;

			for ( column = 0 ; column < gc_buffer_columns ; index++, column++ )
			{
				if ( gc_buffer_attributes[index] != gc_buffer_attributes[index - jump] || 
				     gc_buffer_characters[index] != gc_buffer_characters[index - jump] || 
				     gc_buffer_colorcodes[index] != gc_buffer_colorcodes[index - jump] )
				{
					if ( gc_color_code != gc_buffer_colorcodes[index - jump] )
					{
						gc_update_color(COLOR_CODE_GET(gc_buffer_colorcodes[index - jump], TRUE ), TRUE );
						gc_update_color(COLOR_CODE_GET(gc_buffer_colorcodes[index - jump], FALSE), FALSE);
					}

					if ( gc_buffer_colorcodes[index] != gc_buffer_colorcodes[index - jump] )
					{
						gc_ops.paint_char( /* xx             */ column,
						                   /* yy             */ row,
						                   /* ch             */ gc_buffer_characters[index - jump],
						                   /* attrs          */ gc_buffer_attributes[index - jump],
						                   /* ch_previous    */ 0,
						                   /* attrs_previous */ 0 );
					}
					else
					{
						gc_ops.paint_char( /* xx             */ column,
						                   /* yy             */ row,
						                   /* ch             */ gc_buffer_characters[index - jump],
						                   /* attrs          */ gc_buffer_attributes[index - jump],
						                   /* ch_previous    */ gc_buffer_characters[index],
						                   /* attrs_previous */ gc_buffer_attributes[index] );
					}

					gc_buffer_attributes[index] = gc_buffer_attributes[index - jump];
					gc_buffer_characters[index] = gc_buffer_characters[index - jump];
					gc_buffer_colorcodes[index] = gc_buffer_colorcodes[index - jump];
				}
			}
		}

		if ( colorcodesave != gc_color_code )
		{
			gc_update_color(COLOR_CODE_GET(colorcodesave, TRUE ), TRUE );
			gc_update_color(COLOR_CODE_GET(colorcodesave, FALSE), FALSE);
		}

		/* Now set the freed up lines to the background colour */

		for ( row = top ; row < top + num ; row++ )
		{
			index = row * gc_buffer_columns;

			for ( column = 0 ; column < gc_buffer_columns ; index++, column++ )
			{
				if ( gc_buffer_attributes[index] != ATTR_NONE     || 
				     gc_buffer_characters[index] != ' '           || 
				     gc_buffer_colorcodes[index] != gc_color_code )
				{
					if ( gc_buffer_colorcodes[index] != gc_color_code )
					{
						gc_ops.paint_char( /* xx             */ column,
						                   /* yy             */ row,
						                   /* ch             */ ' ',
						                   /* attrs          */ ATTR_NONE,
						                   /* ch_previous    */ 0,
						                   /* attrs_previous */ 0 );
					}
					else
					{
						gc_ops.paint_char( /* xx             */ column,
						                   /* yy             */ row,
						                   /* ch             */ ' ',
						                   /* attrs          */ ATTR_NONE,
						                   /* ch_previous    */ gc_buffer_characters[index],
						                   /* attrs_previous */ gc_buffer_attributes[index] );
					}

					gc_buffer_attributes[index] = ATTR_NONE;
					gc_buffer_characters[index] = ' ';
					gc_buffer_colorcodes[index] = gc_color_code;
				}
			}
		}
	}
	else
	{
		gc_ops.scroll_down(num, top, bottom);

		/* Now set the freed up lines to the background colour */

		gc_clear_screen(vinfo.v_columns - 1, top + num - 1, top, bottom, 1);
	}
}