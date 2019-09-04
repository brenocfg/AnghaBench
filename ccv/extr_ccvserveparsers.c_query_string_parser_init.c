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
struct TYPE_3__ {int header_index; scalar_t__ on_value; scalar_t__ on_field; void* context; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ query_string_parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  s_query_string_start ; 

void query_string_parser_init(query_string_parser_t* parser, void* context)
{
	parser->state = s_query_string_start;
	parser->context = context;
	parser->header_index = -1;
	parser->on_field = 0;
	parser->on_value = 0;
}