#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uri_parse_state_t ;
struct TYPE_9__ {size_t body; size_t state; size_t resource; TYPE_1__* param_map; scalar_t__ parsed; int /*<<< orphan*/  name; int /*<<< orphan*/  form_data_parser; int /*<<< orphan*/  query_string_parser; } ;
typedef  TYPE_2__ param_parser_t ;
struct TYPE_8__ {scalar_t__ offset; } ;

/* Variables and functions */
#define  URI_CONTENT_BODY 133 
#define  URI_MULTIPART_DATA 132 
#define  URI_MULTIPART_HEADER_FIELD 131 
#define  URI_MULTIPART_HEADER_VALUE 130 
#define  URI_PARSE_TERMINATE 129 
#define  URI_QUERY_STRING 128 
 int /*<<< orphan*/  assert (int) ; 
 size_t find_param_dispatch_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  form_data_parser_execute (int /*<<< orphan*/ *,char const*,size_t,int) ; 
 int /*<<< orphan*/  param_parser_terminate (TYPE_2__*) ; 
 int /*<<< orphan*/  param_type_parser_execute (TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  param_type_parser_init (TYPE_2__*) ; 
 int /*<<< orphan*/  query_string_parser_execute (int /*<<< orphan*/ *,char const*,size_t) ; 
 size_t s_param_skip ; 
 size_t s_param_start ; 

void param_parser_execute(param_parser_t* parser, int resource_id, const char* buf, size_t len, uri_parse_state_t state, int header_index)
{
	switch (state)
	{
		default:
			break;
		case URI_QUERY_STRING:
			query_string_parser_execute(&parser->query_string_parser, buf, len);
			break;
		case URI_CONTENT_BODY:
			if (parser->body == s_param_skip)
				break;
			if (parser->state != s_param_start && parser->state != parser->body)
				param_parser_terminate(parser);
			if (parser->state == s_param_start)
			{
				parser->state = parser->body;
				param_type_parser_init(parser);
			}
			param_type_parser_execute(parser, buf, len);
			break;
		case URI_PARSE_TERMINATE:
			if (parser->state != s_param_start)
				param_parser_terminate(parser); // collect result
			break;
		case URI_MULTIPART_HEADER_FIELD:
		case URI_MULTIPART_HEADER_VALUE:
			if (parser->state != s_param_start)
				param_parser_terminate(parser);
			assert(header_index >= 0);
			form_data_parser_execute(&parser->form_data_parser, buf, len, header_index);
			break;
		case URI_MULTIPART_DATA:
			if (parser->state == s_param_start)
			{
				parser->state = find_param_dispatch_state(parser, parser->name);
				if (parser->state >= 0)
					param_type_parser_init(parser);
			}
			if (parser->state >= 0)
				param_type_parser_execute(parser, buf, len);
			break;
	}
	if (resource_id >= 0 && parser->resource != s_param_start)
		*(int*)(parser->parsed + parser->param_map[parser->resource].offset) = resource_id;
}