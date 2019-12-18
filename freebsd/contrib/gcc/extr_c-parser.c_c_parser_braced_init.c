#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct c_expr {int /*<<< orphan*/  original_code; int /*<<< orphan*/  value; } ;
struct TYPE_8__ {scalar_t__ error; } ;
typedef  TYPE_1__ c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  ERROR_MARK ; 
 int /*<<< orphan*/  c_parser_consume_token (TYPE_1__*) ; 
 int /*<<< orphan*/  c_parser_initelt (TYPE_1__*) ; 
 scalar_t__ c_parser_next_token_is (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 struct c_expr pop_init_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_init_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  really_start_incremental_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct c_expr
c_parser_braced_init (c_parser *parser, tree type, bool nested_p)
{
  gcc_assert (c_parser_next_token_is (parser, CPP_OPEN_BRACE));
  c_parser_consume_token (parser);
  if (nested_p)
    push_init_level (0);
  else
    really_start_incremental_init (type);
  if (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
    {
      if (pedantic)
	pedwarn ("ISO C forbids empty initializer braces");
    }
  else
    {
      /* Parse a non-empty initializer list, possibly with a trailing
	 comma.  */
      while (true)
	{
	  c_parser_initelt (parser);
	  if (parser->error)
	    break;
	  if (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  else
	    break;
	  if (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    break;
	}
    }
  if (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      struct c_expr ret;
      ret.value = error_mark_node;
      ret.original_code = ERROR_MARK;
      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, "expected %<}%>");
      return ret;
    }
  c_parser_consume_token (parser);
  return pop_init_level (0);
}