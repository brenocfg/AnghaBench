#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_12__ {int /*<<< orphan*/  string; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {int result; } ;
struct TYPE_9__ {double result; } ;
struct TYPE_14__ {scalar_t__ state; scalar_t__ cursor; int /*<<< orphan*/  name; TYPE_5__ blob_parser; int /*<<< orphan*/  context; TYPE_4__ string_parser; TYPE_3__ coord_parser; scalar_t__ parsed; TYPE_2__ bool_parser; TYPE_1__ numeric_parser; TYPE_7__* param_map; } ;
typedef  TYPE_6__ param_parser_t ;
struct TYPE_15__ {int type; int /*<<< orphan*/  (* on_blob ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* on_string ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ offset; } ;
typedef  TYPE_7__ param_dispatch_t ;
typedef  int /*<<< orphan*/  ccv_size_t ;
typedef  int /*<<< orphan*/  ccv_point_t ;

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
 int /*<<< orphan*/  ccv_point (int,int) ; 
 int /*<<< orphan*/  ccv_size (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ s_param_start ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void param_parser_terminate(param_parser_t* parser)
{
	if (parser->state >= 0)
	{
		const param_dispatch_t* dispatch = parser->param_map + parser->state;
		switch (dispatch->type)
		{
			case PARAM_TYPE_INT:
				*(int*)(parser->parsed + dispatch->offset) = (int)(parser->numeric_parser.result + 0.5);
				break;
			case PARAM_TYPE_ID:
				if (*(int*)(parser->parsed + dispatch->offset) < 0) // original is illegal resource id
					*(int*)(parser->parsed + dispatch->offset) = (int)(parser->numeric_parser.result + 0.5);
				break;
			case PARAM_TYPE_FLOAT:
				*(float*)(parser->parsed + dispatch->offset) = (float)parser->numeric_parser.result;
				break;
			case PARAM_TYPE_DOUBLE:
				*(double*)(parser->parsed + dispatch->offset) = parser->numeric_parser.result;
				break;
			case PARAM_TYPE_BOOL:
				*(int*)(parser->parsed + dispatch->offset) = parser->bool_parser.result;
				break;
			case PARAM_TYPE_SIZE:
				*(ccv_size_t*)(parser->parsed + dispatch->offset) = ccv_size((int)(parser->coord_parser.x + 0.5), (int)(parser->coord_parser.y + 0.5));
				break;
			case PARAM_TYPE_POINT:
				*(ccv_point_t*)(parser->parsed + dispatch->offset) = ccv_point((int)(parser->coord_parser.x + 0.5), (int)(parser->coord_parser.y + 0.5));
				break;
			case PARAM_TYPE_STRING:
				if (dispatch->on_string)
					dispatch->on_string(parser->context, parser->string_parser.string);
				break;
			case PARAM_TYPE_BLOB:
			case PARAM_TYPE_BODY:
				if (dispatch->on_blob)
					dispatch->on_blob(parser->context, parser->blob_parser.data);
				break;
		}
	}
	if (parser->state != s_param_start)
	{
		parser->state = s_param_start;
		memset(parser->name, 0, sizeof(parser->name));
		parser->cursor = 0;
	}
}