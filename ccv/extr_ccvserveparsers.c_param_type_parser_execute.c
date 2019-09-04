#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
struct TYPE_12__ {int /*<<< orphan*/  state; } ;
struct TYPE_13__ {int /*<<< orphan*/  state; } ;
struct TYPE_11__ {int /*<<< orphan*/  state; } ;
struct TYPE_9__ {size_t state; int /*<<< orphan*/  blob_parser; TYPE_3__ string_parser; TYPE_6__ coord_parser; TYPE_7__ bool_parser; TYPE_5__ numeric_parser; TYPE_1__* param_map; } ;
typedef  TYPE_2__ param_parser_t ;
struct TYPE_8__ {int type; } ;

/* Variables and functions */
#define  PARAM_TYPE_BLOB 137 
#define  PARAM_TYPE_BODY 136 
#define  PARAM_TYPE_BOOL 135 
#define  PARAM_TYPE_DOUBLE 134 
#define  PARAM_TYPE_FLOAT 133 
#define  PARAM_TYPE_ID 132 
#define  PARAM_TYPE_INT 131 
#define  PARAM_TYPE_POINT 130 
#define  PARAM_TYPE_SIZE 129 
#define  PARAM_TYPE_STRING 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blob_parser_execute (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  bool_parser_execute (TYPE_7__*,char const*,size_t) ; 
 int /*<<< orphan*/  coord_parser_execute (TYPE_6__*,char const*,size_t) ; 
 int /*<<< orphan*/  numeric_parser_execute (TYPE_5__*,char const*,size_t) ; 
 int /*<<< orphan*/  s_bool_illegal ; 
 int /*<<< orphan*/  s_coord_illegal ; 
 int /*<<< orphan*/  s_numeric_illegal ; 
 void* s_param_skip ; 
 int /*<<< orphan*/  s_string_overflow ; 
 int /*<<< orphan*/  string_parser_execute (TYPE_3__*,char const*,size_t) ; 

__attribute__((used)) static void param_type_parser_execute(param_parser_t* parser, const char* buf, size_t len)
{
	assert(parser->state >= 0);
	switch (parser->param_map[parser->state].type)
	{
		case PARAM_TYPE_INT:
		case PARAM_TYPE_ID:
		case PARAM_TYPE_FLOAT:
		case PARAM_TYPE_DOUBLE:
			numeric_parser_execute(&parser->numeric_parser, buf, len);
			if (parser->numeric_parser.state == s_numeric_illegal)
				parser->state = s_param_skip;
			break;
		case PARAM_TYPE_BOOL:
			bool_parser_execute(&parser->bool_parser, buf, len);
			if (parser->bool_parser.state == s_bool_illegal)
				parser->state = s_param_skip;
			break;
		case PARAM_TYPE_SIZE:
		case PARAM_TYPE_POINT:
			coord_parser_execute(&parser->coord_parser, buf, len);
			if (parser->coord_parser.state == s_coord_illegal)
				parser->state = s_param_skip;
			break;
		case PARAM_TYPE_STRING:
			string_parser_execute(&parser->string_parser, buf, len);
			if (parser->string_parser.state == s_string_overflow)
				parser->state = s_param_skip;
			break;
		case PARAM_TYPE_BLOB:
		case PARAM_TYPE_BODY:
			blob_parser_execute(&parser->blob_parser, buf, len);
			break;
	}
}