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
struct TYPE_3__ {int state; int result; int division; } ;
typedef  TYPE_1__ numeric_parser_t ;

/* Variables and functions */
#define  s_numeric_after_decimal 131 
#define  s_numeric_before_decimal 130 
#define  s_numeric_illegal 129 
#define  s_numeric_start 128 

void numeric_parser_execute(numeric_parser_t* parser, const char* buf, size_t len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		int digit = buf[i] - '0';
		if ((digit < 0 || digit >= 10) && buf[i] != '.')
			parser->state = s_numeric_illegal;
		switch (parser->state)
		{
			case s_numeric_start:
				parser->result = 0;
				parser->state = s_numeric_before_decimal;
				/* fall-through */
			case s_numeric_before_decimal:
				if (buf[i] != '.')
					parser->result = parser->result * 10 + digit;
				else
					parser->state = s_numeric_after_decimal;
				break;
			case s_numeric_after_decimal:
				if (buf[i] == '.') // we cannot bear another .
					parser->state = s_numeric_illegal;
				else {
					parser->result += digit * parser->division;
					parser->division *= 0.1;
				}
				break;
			case s_numeric_illegal:
				break;
		}
		if (parser->state == s_numeric_illegal)
			break;
	}
}