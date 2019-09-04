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
struct TYPE_3__ {int cs; int top; int /*<<< orphan*/ * new_request; int /*<<< orphan*/  multipart_state; int /*<<< orphan*/ * fragment_mark; int /*<<< orphan*/  uri_mark; int /*<<< orphan*/  path_mark; int /*<<< orphan*/  query_string_mark; int /*<<< orphan*/  header_value_mark; int /*<<< orphan*/  header_field_mark; int /*<<< orphan*/ * current_request; scalar_t__ eating; scalar_t__ chunk_size; int /*<<< orphan*/  stack; } ;
typedef  TYPE_1__ ebb_request_parser ;

/* Variables and functions */
 int /*<<< orphan*/  COPYSTACK (int /*<<< orphan*/ ,int*) ; 
 int EBB_RAGEL_STACK_SIZE ; 
 int ebb_request_parser_start ; 
 int /*<<< orphan*/  s_uninitialized ; 

void ebb_request_parser_init(ebb_request_parser *parser) 
{
  int i;

  int cs = 0;
  int top = 0;
  int stack[EBB_RAGEL_STACK_SIZE];
  
#line 106 "ebb_request_parser.c"
	{
	cs = ebb_request_parser_start;
	top = 0;
	}

#line 415 "ebb_request_parser.rl"
  parser->cs = cs;
  parser->top = top;
  COPYSTACK(parser->stack, stack);

  parser->chunk_size = 0;
  parser->eating = 0;
  
  parser->current_request = NULL;

  parser->header_field_mark = parser->header_value_mark   = 
  parser->query_string_mark = parser->path_mark           = 
  parser->uri_mark          = parser->fragment_mark       = NULL;

  parser->multipart_state = s_uninitialized;
  parser->new_request = NULL;
}