#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct c_declspecs {int /*<<< orphan*/  declspecs_seen_p; } ;
struct c_declarator {int dummy; } ;
struct c_arg_info {int dummy; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_SQUARE ; 
 scalar_t__ CPP_MULT ; 
 scalar_t__ CPP_OPEN_PAREN ; 
 scalar_t__ CPP_OPEN_SQUARE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_STATIC ; 
 struct c_declarator* build_array_declarator (int /*<<< orphan*/ ,struct c_declspecs*,int,int) ; 
 struct c_declarator* build_function_declarator (struct c_arg_info*,struct c_declarator*) ; 
 struct c_declspecs* build_null_declspecs () ; 
 int /*<<< orphan*/  c_parser_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_declspecs (int /*<<< orphan*/ *,struct c_declspecs*,int,int,int) ; 
 TYPE_2__ c_parser_expr_no_commas (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,scalar_t__) ; 
 int c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct c_arg_info* c_parser_parms_declarator (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 struct c_declarator* set_array_declarator_inner (struct c_declarator*,struct c_declarator*,int) ; 

__attribute__((used)) static struct c_declarator *
c_parser_direct_declarator_inner (c_parser *parser, bool id_present,
				  struct c_declarator *inner)
{
  /* Parse a sequence of array declarators and parameter lists.  */
  if (c_parser_next_token_is (parser, CPP_OPEN_SQUARE))
    {
      struct c_declarator *declarator;
      struct c_declspecs *quals_attrs = build_null_declspecs ();
      bool static_seen;
      bool star_seen;
      tree dimen;
      c_parser_consume_token (parser);
      c_parser_declspecs (parser, quals_attrs, false, false, true);
      static_seen = c_parser_next_token_is_keyword (parser, RID_STATIC);
      if (static_seen)
	c_parser_consume_token (parser);
      if (static_seen && !quals_attrs->declspecs_seen_p)
	c_parser_declspecs (parser, quals_attrs, false, false, true);
      if (!quals_attrs->declspecs_seen_p)
	quals_attrs = NULL;
      /* If "static" is present, there must be an array dimension.
	 Otherwise, there may be a dimension, "*", or no
	 dimension.  */
      if (static_seen)
	{
	  star_seen = false;
	  dimen = c_parser_expr_no_commas (parser, NULL).value;
	}
      else
	{
	  if (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	    {
	      dimen = NULL_TREE;
	      star_seen = false;
	    }
	  else if (c_parser_next_token_is (parser, CPP_MULT))
	    {
	      if (c_parser_peek_2nd_token (parser)->type == CPP_CLOSE_SQUARE)
		{
		  dimen = NULL_TREE;
		  star_seen = true;
		  c_parser_consume_token (parser);
		}
	      else
		{
		  star_seen = false;
		  dimen = c_parser_expr_no_commas (parser, NULL).value;
		}
	    }
	  else
	    {
	      star_seen = false;
	      dimen = c_parser_expr_no_commas (parser, NULL).value;
	    }
	}
      if (c_parser_next_token_is (parser, CPP_CLOSE_SQUARE))
	c_parser_consume_token (parser);
      else
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE,
				     "expected %<]%>");
	  return NULL;
	}
      declarator = build_array_declarator (dimen, quals_attrs, static_seen,
					   star_seen);
      if (declarator == NULL)
	return NULL;
      inner = set_array_declarator_inner (declarator, inner, !id_present);
      return c_parser_direct_declarator_inner (parser, id_present, inner);
    }
  else if (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      tree attrs;
      struct c_arg_info *args;
      c_parser_consume_token (parser);
      attrs = c_parser_attributes (parser);
      args = c_parser_parms_declarator (parser, id_present, attrs);
      if (args == NULL)
	return NULL;
      else
	{
	  inner = build_function_declarator (args, inner);
	  return c_parser_direct_declarator_inner (parser, id_present, inner);
	}
    }
  return inner;
}