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
struct TYPE_3__ {int cursor_row; int con_rows; int cursor_col; int con_cols; int saved_col; int saved_row; void* background; void* foreground; } ;
typedef  TYPE_1__ console_data_s ;

/* Variables and functions */
 int /*<<< orphan*/  __console_clear () ; 
 int /*<<< orphan*/  __console_clear_from_cursor () ; 
 int /*<<< orphan*/  __console_clear_line (int,int,int) ; 
 int /*<<< orphan*/  __console_clear_to_cursor () ; 
 void** color_table ; 
 TYPE_1__* curr_con ; 

__attribute__((used)) static int __console_parse_escsequence(char *pchr)
{
	char chr;
	console_data_s *con;
	int i;
	int parameters[3];
	int para;

	if(!curr_con) return -1;
	con = curr_con;

	/* set default value */
	para = 0;
	parameters[0] = 0;
	parameters[1] = 0;
	parameters[2] = 0;

	/* scan parameters */
	i = 0;
	chr = *pchr;
	while( (para < 3) && (chr >= '0') && (chr <= '9') )
	{
		while( (chr >= '0') && (chr <= '9') )
		{
			/* parse parameter */
			parameters[para] *= 10;
			parameters[para] += chr - '0';
			pchr++;
			i++;
			chr = *pchr;
		}
		para++;

		if( *pchr == ';' )
		{
		  /* skip parameter delimiter */
		  pchr++;
			i++;
		}
		chr = *pchr;
	}

	/* get final character */
	chr = *pchr++;
	i++;
	switch(chr)
	{
		/////////////////////////////////////////
		// Cursor directional movement
		/////////////////////////////////////////
		case 'A':
		{
			curr_con->cursor_row -= parameters[0];
			if(curr_con->cursor_row < 0) curr_con->cursor_row = 0;
			break;
		}
		case 'B':
		{
			curr_con->cursor_row += parameters[0];
			if(curr_con->cursor_row >= curr_con->con_rows) curr_con->cursor_row = curr_con->con_rows - 1;
			break;
		}
		case 'C':
		{
			curr_con->cursor_col += parameters[0];
			if(curr_con->cursor_col >= curr_con->con_cols) curr_con->cursor_col = curr_con->con_cols - 1;
			break;
		}
		case 'D':
		{
			curr_con->cursor_col -= parameters[0];
			if(curr_con->cursor_col < 0) curr_con->cursor_col = 0;
			break;
		}
		/////////////////////////////////////////
		// Cursor position movement
		/////////////////////////////////////////
		case 'H':
		case 'f':
		{
			curr_con->cursor_col = parameters[1];
			curr_con->cursor_row = parameters[0];
			if(curr_con->cursor_row >= curr_con->con_rows) curr_con->cursor_row = curr_con->con_rows - 1;
			if(curr_con->cursor_col >= curr_con->con_cols) curr_con->cursor_col = curr_con->con_cols - 1;
			break;
		}
		/////////////////////////////////////////
		// Screen clear
		/////////////////////////////////////////
		case 'J':
		{
			if( parameters[0] == 0 )
        __console_clear_from_cursor();
			if( parameters[0] == 1 )
        __console_clear_to_cursor();
			if( parameters[0] == 2 )
        __console_clear();

			break;
		}
		/////////////////////////////////////////
		// Line clear
		/////////////////////////////////////////
		case 'K':
		{
			if( parameters[0] == 0 )
        __console_clear_line( curr_con->cursor_row, curr_con->cursor_col, curr_con->con_cols );
			if( parameters[0] == 1 )
        __console_clear_line( curr_con->cursor_row, 0, curr_con->cursor_col );
			if( parameters[0] == 2 )
        __console_clear_line( curr_con->cursor_row, 0, curr_con->con_cols);

			break;
		}
		/////////////////////////////////////////
		// Save cursor position
		/////////////////////////////////////////
		case 's':
		{
			con->saved_col = con->cursor_col;
			con->saved_row = con->cursor_row;
			break;
		}
		/////////////////////////////////////////
		// Load cursor position
		/////////////////////////////////////////
		case 'u':
			con->cursor_col = con->saved_col;
			con->cursor_row = con->saved_row;
			break;
		/////////////////////////////////////////
		// SGR Select Graphic Rendition
		/////////////////////////////////////////
		case 'm':
		{
			// handle 30-37,39 for foreground color changes
			if( (parameters[0] >= 30) && (parameters[0] <= 39) )
			{
				parameters[0] -= 30;

				//39 is the reset code
				if(parameters[0] == 9){
				    parameters[0] = 15;
				}
				else if(parameters[0] > 7){
					parameters[0] = 7;
				}

				if(parameters[1] == 1)
				{
					// Intensity: Bold makes color bright
					parameters[0] += 8;
				}
				con->foreground = color_table[parameters[0]];
			}
			// handle 40-47 for background color changes
			else if( (parameters[0] >= 40) && (parameters[0] <= 47) )
			{
				parameters[0] -= 40;

				if(parameters[1] == 1)
				{
					// Intensity: Bold makes color bright
					parameters[0] += 8;
				}
				con->background = color_table[parameters[0]];
			}
		  break;
		}
	}

	return(i);
}