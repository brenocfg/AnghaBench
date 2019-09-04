#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t state; int /*<<< orphan*/  blob_parser; int /*<<< orphan*/  string_parser; int /*<<< orphan*/  coord_parser; int /*<<< orphan*/  bool_parser; int /*<<< orphan*/  numeric_parser; TYPE_1__* param_map; } ;
typedef  TYPE_2__ param_parser_t ;
struct TYPE_4__ {int type; } ;

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
 int /*<<< orphan*/  blob_parser_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bool_parser_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coord_parser_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numeric_parser_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_parser_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void param_type_parser_init(param_parser_t* parser)
{
	assert(parser->state >= 0);
	switch (parser->param_map[parser->state].type)
	{
		case PARAM_TYPE_INT:
		case PARAM_TYPE_ID:
		case PARAM_TYPE_FLOAT:
		case PARAM_TYPE_DOUBLE:
			numeric_parser_init(&parser->numeric_parser);
			break;
		case PARAM_TYPE_BOOL:
			bool_parser_init(&parser->bool_parser);
			break;
		case PARAM_TYPE_SIZE:
		case PARAM_TYPE_POINT:
			coord_parser_init(&parser->coord_parser);
			break;
		case PARAM_TYPE_STRING:
			string_parser_init(&parser->string_parser);
			break;
		case PARAM_TYPE_BLOB:
		case PARAM_TYPE_BODY:
			blob_parser_init(&parser->blob_parser);
			break;
	}
}