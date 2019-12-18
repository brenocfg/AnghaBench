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
struct TYPE_3__ {int state; int x; int y; int division; } ;
typedef  TYPE_1__ coord_parser_t ;

/* Variables and functions */
#define  s_coord_illegal 133 
#define  s_coord_start 132 
#define  s_coord_x_after_decimal 131 
#define  s_coord_x_before_decimal 130 
#define  s_coord_y_after_decimal 129 
#define  s_coord_y_before_decimal 128 

void coord_parser_execute(coord_parser_t* parser, const char* buf, size_t len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		int digit = buf[i] - '0';
		if ((digit < 0 || digit >= 10) && buf[i] != '.' && buf[i] != 'x' && buf[i] != 'X')
			parser->state = s_coord_illegal;
		switch (parser->state)
		{
			case s_coord_start:
				parser->x = parser->y = 0;
				parser->state = s_coord_x_before_decimal;
				/* fall-through */
			case s_coord_x_before_decimal:
				if (buf[i] != 'x' && buf[i] != 'X')
				{
					if (buf[i] != '.')
						parser->x = parser->x * 10 + digit;
					else
						parser->state = s_coord_x_after_decimal;
				} else
					parser->state = s_coord_y_before_decimal;
				break;
			case s_coord_x_after_decimal:
				if (buf[i] != 'x' && buf[i] != 'X')
				{
					if (buf[i] == '.')
					{
						parser->state = s_coord_illegal;
						break;
					}
					parser->x += digit * parser->division;
					parser->division *= 0.1;
				} else {
					parser->division = 0.1;
					parser->state = s_coord_y_before_decimal;
				}
				break;
			case s_coord_y_before_decimal:
				if (buf[i] == 'x' || buf[i] == 'X')
				{
					parser->state = s_coord_illegal;
					break;
				}
				if (buf[i] != '.')
					parser->y = parser->y * 10 + digit;
				else
					parser->state = s_coord_y_after_decimal;
				break;
			case s_coord_y_after_decimal:
				if (buf[i] == 'x' || buf[i] == 'X' || buf[i] == '.')
				{
					parser->state = s_coord_illegal;
					break;
				}
				parser->y += digit * parser->division;
				parser->division *= 0.1;
				break;
			case s_coord_illegal:
				break;
		}
		if (parser->state == s_coord_illegal)
			break;
	}
}