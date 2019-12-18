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
typedef  int /*<<< orphan*/ * tree ;
struct c_parm {int dummy; } ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_COLON ; 
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_ELLIPSIS ; 
 int /*<<< orphan*/  CPP_NAME ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_ATTRIBUTE ; 
 int /*<<< orphan*/  TREE_LIST ; 
 int /*<<< orphan*/ * build_tree_list (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_attributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * c_parser_objc_selector (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_objc_type_name (int /*<<< orphan*/ *) ; 
 struct c_parm* c_parser_parameter_declaration (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * chainon (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  grokparm (struct c_parm*) ; 
 int /*<<< orphan*/ * make_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * objc_build_keyword_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * objc_build_method_signature (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ objc_method_attributes ; 

__attribute__((used)) static tree
c_parser_objc_method_decl (c_parser *parser)
{
  tree type = NULL_TREE;
  tree sel;
  tree parms = NULL_TREE;
  bool ellipsis = false;

  if (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
    {
      c_parser_consume_token (parser);
      type = c_parser_objc_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
    }
  sel = c_parser_objc_selector (parser);
  /* If there is no selector, or a colon follows, we have an
     objc-keyword-selector.  If there is a selector, and a colon does
     not follow, that selector ends the objc-method-decl.  */
  if (!sel || c_parser_next_token_is (parser, CPP_COLON))
    {
      tree tsel = sel;
      tree list = NULL_TREE;
      while (true)
	{
	  /* APPLE LOCAL radar 4157812 */
	  tree attr = NULL_TREE;
	  tree atype = NULL_TREE, id, keyworddecl;
	  if (!c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    break;
	  if (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	    {
	      c_parser_consume_token (parser);
	      atype = c_parser_objc_type_name (parser);
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					 "expected %<)%>");
	    }
	  /* APPLE LOCAL begin radar 4157812 */
	  if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    attr = c_parser_attributes (parser);
	  /* APPLE LOCAL end radar 4157812 */
	  if (c_parser_next_token_is_not (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected identifier");
	      return error_mark_node;
	    }
	  id = c_parser_peek_token (parser)->value;
	  c_parser_consume_token (parser);
	  /* APPLE LOCAL radar 4157812 */
	  keyworddecl = objc_build_keyword_decl (tsel, atype, id, attr);
	  list = chainon (list, keyworddecl);
	  tsel = c_parser_objc_selector (parser);
	  if (!tsel && c_parser_next_token_is_not (parser, CPP_COLON))
	    break;
	}
      /* APPLE LOCAL begin radar 3803157 - objc attribute (in 4.2 y) */
      if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	objc_method_attributes = c_parser_attributes (parser);
      /* APPLE LOCAL end radar 3803157 - objc attribute (in 4.2 y) */
      /* Parse the optional parameter list.  Optional Objective-C
	 method parameters follow the C syntax, and may include '...'
	 to denote a variable number of arguments.  */
      parms = make_node (TREE_LIST);
      while (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  struct c_parm *parm;
	  c_parser_consume_token (parser);
	  if (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	    {
	      ellipsis = true;
	      c_parser_consume_token (parser);
	      /* APPLE LOCAL end radar 3803157 - objc attribute (in 4.2 y) */
	      if (objc_method_attributes)
		error ("method attributes must be specified at the end only");
	      if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		objc_method_attributes = c_parser_attributes (parser);
	      /* APPLE LOCAL end radar 3803157 - objc attribute (in 4.2 y) */
	      break;
	    }
	  parm = c_parser_parameter_declaration (parser, NULL_TREE);
	  if (parm == NULL)
	    break;
	  parms = chainon (parms,
			   build_tree_list (NULL_TREE, grokparm (parm)));
	}
      sel = list;
    }
  /* APPLE LOCAL begin radar 3803157 - objc attribute (in 4.2 y) */
  else
    {
      gcc_assert (objc_method_attributes == NULL_TREE);
      if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	objc_method_attributes = c_parser_attributes (parser);
    }
  /* APPLE LOCAL end radar 3803157 - objc attribute (in 4.2 y) */
  /* APPLE LOCAL begin radar 4157812 */
  if (sel == NULL)
    {
      c_parser_error (parser, "objective-c method declaration is expected");
      return error_mark_node;
    }
  /* APPLE LOCAL end radar 4157812 */
  return objc_build_method_signature (type, sel, parms, ellipsis);
}