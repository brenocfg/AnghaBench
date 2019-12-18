#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct c_typespec {int /*<<< orphan*/  kind; int /*<<< orphan*/  spec; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int keyword; scalar_t__ id_kind; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_BRACE ; 
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  CPP_PRAGMA ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 scalar_t__ C_ID_CLASSNAME ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int RECORD_TYPE ; 
 int /*<<< orphan*/  RID_AT_DEFS ; 
#define  RID_STRUCT 129 
#define  RID_UNION 128 
 int UNION_TYPE ; 
 int /*<<< orphan*/  c_dialect_objc () ; 
 int /*<<< orphan*/  c_parser_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_pragma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_struct_declaration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chainon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctsk_tagdef ; 
 int /*<<< orphan*/  ctsk_tagref ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  finish_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  nreverse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_get_class_ivars (int /*<<< orphan*/ ) ; 
 struct c_typespec parser_xref_tag (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  pragma_external ; 
 int /*<<< orphan*/  start_struct (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct c_typespec
c_parser_struct_or_union_specifier (c_parser *parser)
{
  struct c_typespec ret;
  tree attrs;
  tree ident = NULL_TREE;
  enum tree_code code;
  switch (c_parser_peek_token (parser)->keyword)
    {
    case RID_STRUCT:
      code = RECORD_TYPE;
      break;
    case RID_UNION:
      code = UNION_TYPE;
      break;
    default:
      gcc_unreachable ();
    }
  c_parser_consume_token (parser);
  attrs = c_parser_attributes (parser);
  if (c_parser_next_token_is (parser, CPP_NAME))
    {
      ident = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
    }
  if (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
    {
      /* Parse a struct or union definition.  Start the scope of the
	 tag before parsing components.  */
      tree type = start_struct (code, ident);
      tree postfix_attrs;
      /* We chain the components in reverse order, then put them in
	 forward order at the end.  Each struct-declaration may
	 declare multiple components (comma-separated), so we must use
	 chainon to join them, although when parsing each
	 struct-declaration we can use TREE_CHAIN directly.

	 The theory behind all this is that there will be more
	 semicolon separated fields than comma separated fields, and
	 so we'll be minimizing the number of node traversals required
	 by chainon.  */
      tree contents = NULL_TREE;
      c_parser_consume_token (parser);
      /* Handle the Objective-C @defs construct,
	 e.g. foo(sizeof(struct{ @defs(ClassName) }));.  */
      if (c_parser_next_token_is_keyword (parser, RID_AT_DEFS))
	{
	  tree name;
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    goto end_at_defs;
	  if (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_CLASSNAME)
	    {
	      name = c_parser_peek_token (parser)->value;
	      c_parser_consume_token (parser);
	    }
	  else
	    {
	      c_parser_error (parser, "expected class name");
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
	      goto end_at_defs;
	    }
	  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				     "expected %<)%>");
	  contents = nreverse (objc_get_class_ivars (name));
	}
    end_at_defs:
      /* Parse the struct-declarations and semicolons.  Problems with
	 semicolons are diagnosed here; empty structures are diagnosed
	 elsewhere.  */
      while (true)
	{
	  tree decls;
	  /* Parse any stray semicolon.  */
	  if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      if (pedantic)
		pedwarn ("extra semicolon in struct or union specified");
	      c_parser_consume_token (parser);
	      continue;
	    }
	  /* Stop if at the end of the struct or union contents.  */
	  if (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
	    {
	      c_parser_consume_token (parser);
	      break;
	    }
	  /* Accept #pragmas at struct scope.  */
	  if (c_parser_next_token_is (parser, CPP_PRAGMA))
	    {
	      c_parser_pragma (parser, pragma_external);
	      continue;
	    }
	  /* Parse some comma-separated declarations, but not the
	     trailing semicolon if any.  */
	  decls = c_parser_struct_declaration (parser);
	  contents = chainon (decls, contents);
	  /* If no semicolon follows, either we have a parse error or
	     are at the end of the struct or union and should
	     pedwarn.  */
	  if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    c_parser_consume_token (parser);
	  else
	    {
	      if (c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		pedwarn ("no semicolon at end of struct or union");
	      else
		{
		  c_parser_error (parser, "expected %<;%>");
		  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, NULL);
		  break;
		}
	    }
	}
      postfix_attrs = c_parser_attributes (parser);
      ret.spec = finish_struct (type, nreverse (contents),
				chainon (attrs, postfix_attrs));
      ret.kind = ctsk_tagdef;
      return ret;
    }
  else if (!ident)
    {
      c_parser_error (parser, "expected %<{%>");
      ret.spec = error_mark_node;
      ret.kind = ctsk_tagref;
      return ret;
    }
  ret = parser_xref_tag (code, ident);
  return ret;
}