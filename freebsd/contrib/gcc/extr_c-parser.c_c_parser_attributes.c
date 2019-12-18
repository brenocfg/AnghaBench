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
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {int keyword; scalar_t__ id_kind; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ CPP_CLOSE_PAREN ; 
 scalar_t__ CPP_COMMA ; 
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ C_ID_ID ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_ATTRIBUTE ; 
#define  RID_AUTO 151 
#define  RID_BOOL 150 
#define  RID_CHAR 149 
#define  RID_COMPLEX 148 
#define  RID_CONST 147 
#define  RID_DFLOAT128 146 
#define  RID_DFLOAT32 145 
#define  RID_DFLOAT64 144 
#define  RID_DOUBLE 143 
#define  RID_EXTERN 142 
#define  RID_FLOAT 141 
#define  RID_INLINE 140 
#define  RID_INT 139 
#define  RID_LONG 138 
#define  RID_REGISTER 137 
#define  RID_RESTRICT 136 
#define  RID_SHORT 135 
#define  RID_SIGNED 134 
#define  RID_STATIC 133 
#define  RID_THREAD 132 
#define  RID_TYPEDEF 131 
#define  RID_UNSIGNED 130 
#define  RID_VOID 129 
#define  RID_VOLATILE 128 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int c_lex_string_translate ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_expr_list (int /*<<< orphan*/ *,int) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  chainon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
c_parser_attributes (c_parser *parser)
{
  tree attrs = NULL_TREE;
  while (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
    {
      /* ??? Follow the C++ parser rather than using the
	 c_lex_string_translate kludge.  */
      c_lex_string_translate = 0;
      c_parser_consume_token (parser);
      if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  c_lex_string_translate = 1;
	  return attrs;
	}
      if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	{
	  c_lex_string_translate = 1;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
	  return attrs;
	}
      /* Parse the attribute list.  */
      while (c_parser_next_token_is (parser, CPP_COMMA)
	     || c_parser_next_token_is (parser, CPP_NAME)
	     || c_parser_next_token_is (parser, CPP_KEYWORD))
	{
	  tree attr, attr_name, attr_args;
	  if (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      continue;
	    }
	  if (c_parser_next_token_is (parser, CPP_KEYWORD))
	    {
	      /* ??? See comment above about what keywords are
		 accepted here.  */
	      bool ok;
	      switch (c_parser_peek_token (parser)->keyword)
		{
		case RID_STATIC:
		case RID_UNSIGNED:
		case RID_LONG:
		case RID_CONST:
		case RID_EXTERN:
		case RID_REGISTER:
		case RID_TYPEDEF:
		case RID_SHORT:
		case RID_INLINE:
		case RID_VOLATILE:
		case RID_SIGNED:
		case RID_AUTO:
		case RID_RESTRICT:
		case RID_COMPLEX:
		case RID_THREAD:
		case RID_INT:
		case RID_CHAR:
		case RID_FLOAT:
		case RID_DOUBLE:
		case RID_VOID:
		case RID_DFLOAT32:
		case RID_DFLOAT64:
		case RID_DFLOAT128:
		case RID_BOOL:
		  ok = true;
		  break;
		default:
		  ok = false;
		  break;
		}
	      if (!ok)
		break;
	    }
	  attr_name = c_parser_peek_token (parser)->value;
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
	    {
	      attr = build_tree_list (attr_name, NULL_TREE);
	      attrs = chainon (attrs, attr);
	      continue;
	    }
	  c_parser_consume_token (parser);
	  /* Parse the attribute contents.  If they start with an
	     identifier which is followed by a comma or close
	     parenthesis, then the arguments start with that
	     identifier; otherwise they are an expression list.  */
	  if (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && ((c_parser_peek_2nd_token (parser)->type == CPP_COMMA)
		  || (c_parser_peek_2nd_token (parser)->type
		      == CPP_CLOSE_PAREN)))
	    {
	      tree arg1 = c_parser_peek_token (parser)->value;
	      c_parser_consume_token (parser);
	      if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		attr_args = build_tree_list (NULL_TREE, arg1);
	      else
		{
		  c_parser_consume_token (parser);
		  attr_args = tree_cons (NULL_TREE, arg1,
					 c_parser_expr_list (parser, false));
		}
	    }
	  else
	    {
	      if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
		attr_args = NULL_TREE;
	      else
		attr_args = c_parser_expr_list (parser, false);
	    }
	  attr = build_tree_list (attr_name, attr_args);
	  if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	    c_parser_consume_token (parser);
	  else
	    {
	      c_lex_string_translate = 1;
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	      return attrs;
	    }
	  attrs = chainon (attrs, attr);
	}
      if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      else
	{
	  c_lex_string_translate = 1;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  return attrs;
	}
      if (c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_consume_token (parser);
      else
	{
	  c_lex_string_translate = 1;
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  return attrs;
	}
      c_lex_string_translate = 1;
    }
  return attrs;
}