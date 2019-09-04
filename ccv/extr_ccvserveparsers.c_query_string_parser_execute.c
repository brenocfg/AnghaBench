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
struct TYPE_3__ {int state; int /*<<< orphan*/  header_index; int /*<<< orphan*/  context; int /*<<< orphan*/  (* on_value ) (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* on_field ) (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ query_string_parser_t ;

/* Variables and functions */
#define  s_query_string_field_start 131 
#define  s_query_string_start 130 
#define  s_query_string_value_done 129 
#define  s_query_string_value_start 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 

void query_string_parser_execute(query_string_parser_t* parser, const char* buf, size_t len)
{
	int i;
	size_t field_len = 0;
	const char* field_mark = buf;
	size_t value_len = 0;
	const char* value_mark = buf;
	for (i = 0; i < len; i++)
		switch (parser->state)
		{
			case s_query_string_start:
				parser->state = s_query_string_field_start;
				++parser->header_index;
				field_mark = buf + i;
				field_len = 0;
				/* fall-through */
			case s_query_string_field_start:
				if (buf[i] != '&')
				{
					if (buf[i] == '=')
					{
						parser->state = s_query_string_value_start;
						// setup value_len
						value_mark = buf + i + 1;
						value_len = 0;
					}
					if (parser->state == s_query_string_field_start)
						field_len = buf + i + 1 - field_mark;
					break;
				} else
					// it is marked as the start state, then quickly turns to done state
					parser->state = s_query_string_value_start;
					/* fall-through */
			case s_query_string_value_start:
				if (field_len > 0 && parser->on_field)
				{
					parser->on_field(parser->context, field_mark, field_len, parser->header_index);
					field_len = 0;
				}
				if (buf[i] != '&')
				{
					value_len = buf + i + 1 - value_mark;
					break;
				} else
					parser->state = s_query_string_value_done;
					/* fall-through */
			case s_query_string_value_done:
				// reset field_len
				field_mark = buf + i + 1;
				field_len = 0;
				if (value_len > 0 && parser->on_value)
				{
					parser->on_value(parser->context, value_mark, value_len, parser->header_index);
					// reset value_len
					value_len = 0;
				}
				++parser->header_index;
				parser->state = s_query_string_field_start;
				break;
		}
	if (field_len > 0 && parser->state == s_query_string_field_start && parser->on_field)
		parser->on_field(parser->context, field_mark, field_len, parser->header_index);
	else if (value_len > 0 && parser->state == s_query_string_value_start && parser->on_value)
		parser->on_value(parser->context, value_mark, value_len, parser->header_index);
}