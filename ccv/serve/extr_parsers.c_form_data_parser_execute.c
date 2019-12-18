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
typedef  int /*<<< orphan*/  name ;
struct TYPE_3__ {int state; size_t cursor; int disposition_index; char lookbehind; int /*<<< orphan*/  context; int /*<<< orphan*/  (* on_name ) (int /*<<< orphan*/ ,char const*,size_t) ;} ;
typedef  TYPE_1__ form_data_parser_t ;
typedef  int /*<<< orphan*/  form_data ;
typedef  int /*<<< orphan*/  content_disposition ;

/* Variables and functions */
 int s_form_data_done ; 
#define  s_form_data_header_field 132 
#define  s_form_data_header_value_name_done 131 
#define  s_form_data_header_value_name_start 130 
#define  s_form_data_header_value_start 129 
#define  s_form_data_start 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char const*,size_t) ; 
 int tolower (char const) ; 

void form_data_parser_execute(form_data_parser_t* parser, const char* buf, size_t len, int header_index)
{
	static const char content_disposition[] = "content-disposition";
	static const char form_data[] = "form-data;";
	static const char name[] = "name=\"";

	int i, cl;
	size_t name_len = 0;
	const char* name_mark = buf;
	for (i = 0; i < len; i++)
	{
		cl = tolower(buf[i]);
		switch (parser->state)
		{
			default:
				// illegal state, just reset and return
				parser->state = s_form_data_start;
				/* fall-through */
			case s_form_data_start:
				parser->state = s_form_data_header_field;
				parser->cursor = 0;
				/* fall-through */
			case s_form_data_header_field:
				// only care about Content-Disposition
				if (cl != content_disposition[parser->cursor])
				{
					parser->state = s_form_data_start; // reset the state
					return;
				}
				++parser->cursor;
				if (parser->cursor == sizeof(content_disposition) - 1)
				{
					parser->disposition_index = header_index;
					parser->state = s_form_data_header_value_start;
					parser->cursor = 0;
				}
				break;
			case s_form_data_header_value_start:
				if (cl == ' ' || cl == '\t') // ignore space or tab
					continue;
				if (cl != form_data[parser->cursor])
				{
					parser->state = s_form_data_start; // we don't accept other disposition other than form-data
					return;
				}
				++parser->cursor;
				if (parser->cursor == sizeof(form_data) - 1)
				{
					// verified form-data, now get the name parameter
					parser->state = s_form_data_header_value_name_start;
					parser->cursor = 0;
				}
				break;
			case s_form_data_header_value_name_start:
				if (cl == ' ' || cl == '\t') // ignore space or tab
					continue;
				if (cl != name[parser->cursor])
				{
					parser->state = s_form_data_start; // we only accepts name parameter for form-data here
					return;
				}
				++parser->cursor;
				if (parser->cursor == sizeof(name) - 1)
				{
					parser->state = s_form_data_header_value_name_done;
					parser->lookbehind = '\0';
					parser->cursor = 0;
					name_mark = buf + i + 1;
					name_len = 0;
				}
				break;
			case s_form_data_header_value_name_done:
				if (parser->lookbehind != '\\' && buf[i] == '"')
				{
					parser->state = s_form_data_done; // the end of quote, return
					if (name_len > 0 && parser->on_name)
						parser->on_name(parser->context, name_mark, name_len);
					return;
				}
				name_len = buf + i + 1 - name_mark;
				// the lookbehind is only used for escape \, and if it is \ already
				// we will skip the current one, otherwise, we don't
				parser->lookbehind = (parser->lookbehind != '\\') ? buf[i] : '\0';
				break;
		}
	}
	if (name_len > 0 && parser->state == s_form_data_header_value_name_done && parser->on_name)
		parser->on_name(parser->context, name_mark, name_len);
}