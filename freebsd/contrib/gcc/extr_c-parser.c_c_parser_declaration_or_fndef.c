#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct c_expr {scalar_t__ value; } ;
struct c_declspecs {scalar_t__ attrs; int /*<<< orphan*/  declspecs_seen_p; scalar_t__ type_seen_p; scalar_t__ non_sc_seen_p; } ;
struct c_declarator {TYPE_1__* declarator; } ;
struct TYPE_21__ {scalar_t__ error; } ;
typedef  TYPE_2__ c_parser ;
struct TYPE_22__ {scalar_t__ location; } ;
struct TYPE_20__ {scalar_t__ kind; } ;
typedef  scalar_t__ DECL_SOURCE_LOCATION ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_COMMA ; 
 int /*<<< orphan*/  CPP_EOF ; 
 int /*<<< orphan*/  CPP_EQ ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_SEMICOLON ; 
 int /*<<< orphan*/  C_DTR_NORMAL ; 
 int /*<<< orphan*/  DECL_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_ASM ; 
 int /*<<< orphan*/  RID_ATTRIBUTE ; 
 int /*<<< orphan*/  RID_AT_IMPLEMENTATION ; 
 int /*<<< orphan*/  RID_AT_INTERFACE ; 
 int /*<<< orphan*/  RID_AT_PROTOCOL ; 
 int /*<<< orphan*/  RID_IN ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  add_stmt (scalar_t__) ; 
 struct c_declspecs* build_null_declspecs () ; 
 scalar_t__ build_stmt (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* c_dialect_objc () ; 
 scalar_t__ c_parser_attributes (TYPE_2__*) ; 
 scalar_t__ c_parser_compound_statement (TYPE_2__*) ; 
 int /*<<< orphan*/  c_parser_consume_token (TYPE_2__*) ; 
 struct c_declarator* c_parser_declarator (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  c_parser_declspecs (TYPE_2__*,struct c_declspecs*,int,int,int) ; 
 int /*<<< orphan*/  c_parser_error (TYPE_2__*,char*) ; 
 struct c_expr c_parser_initializer (TYPE_2__*) ; 
 scalar_t__ c_parser_next_token_is (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_not (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_class_definition (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  c_parser_objc_protocol_definition (TYPE_2__*,scalar_t__) ; 
 TYPE_5__* c_parser_peek_token (TYPE_2__*) ; 
 scalar_t__ c_parser_simple_asm_expr (TYPE_2__*) ; 
 int /*<<< orphan*/  c_parser_skip_to_end_of_block_or_statement (TYPE_2__*) ; 
 scalar_t__ cdk_block_pointer ; 
 scalar_t__ chainon (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  finish_decl (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  finish_declspecs (struct c_declspecs*) ; 
 int /*<<< orphan*/  finish_function () ; 
 int /*<<< orphan*/  finish_init () ; 
 scalar_t__ flag_nested_functions ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__*) ; 
 int /*<<< orphan*/  global_bindings_p () ; 
 int /*<<< orphan*/  maybe_warn_string_init (int /*<<< orphan*/ ,struct c_expr) ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  pending_xref_error () ; 
 int /*<<< orphan*/  pop_function_context () ; 
 int /*<<< orphan*/  push_function_context () ; 
 int /*<<< orphan*/  shadow_tag (struct c_declspecs*) ; 
 int /*<<< orphan*/  shadow_tag_warned (struct c_declspecs*,int) ; 
 scalar_t__ start_decl (struct c_declarator*,struct c_declspecs*,int,scalar_t__) ; 
 int /*<<< orphan*/  start_function (struct c_declspecs*,struct c_declarator*,scalar_t__) ; 
 int /*<<< orphan*/  start_init (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_parm_decls () ; 

__attribute__((used)) static void
c_parser_declaration_or_fndef (c_parser *parser, bool fndef_ok, bool empty_ok,
			       /* APPLE LOCAL radar 4708210 (for_objc_collection in 4.2) */
			       bool nested, bool start_attr_ok, tree *foreach_elem)
{
  struct c_declspecs *specs;
  tree prefix_attrs;
  tree all_prefix_attrs;
  bool diagnosed_no_specs = false;

  specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, true, true, start_attr_ok);
  if (parser->error)
    {
      c_parser_skip_to_end_of_block_or_statement (parser);
      return;
    }
  if (nested && !specs->declspecs_seen_p)
    {
      c_parser_error (parser, "expected declaration specifiers");
      c_parser_skip_to_end_of_block_or_statement (parser);
      return;
    }
  finish_declspecs (specs);
  if (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      if (empty_ok)
	shadow_tag (specs);
      else
	{
	  shadow_tag_warned (specs, 1);
	  pedwarn ("empty declaration");
	}
      c_parser_consume_token (parser);
      return;
    }
  /* APPLE LOCAL begin radar 4548636 - class attributes. */
  else if (c_parser_next_token_is_keyword (parser, RID_AT_INTERFACE) 
	   || c_parser_next_token_is_keyword (parser, RID_AT_IMPLEMENTATION))
    {
      gcc_assert (c_dialect_objc ());
      if (!specs->declspecs_seen_p || specs->attrs == NULL_TREE
	  || specs->type_seen_p || specs->non_sc_seen_p)
	c_parser_error (parser, "no type or storage class may be specified here");
      c_parser_objc_class_definition (parser, specs->attrs);
      return;
    }
  /* APPLE LOCAL end radar 4548636 - class attributes. */
  /* APPLE LOCAL begin radar 4947311 - protocol attributes */
  else if (c_parser_next_token_is_keyword (parser, RID_AT_PROTOCOL))
    {
      gcc_assert (c_dialect_objc ());
      if (!specs->declspecs_seen_p || specs->attrs == NULL_TREE
	  || specs->type_seen_p || specs->non_sc_seen_p)
	c_parser_error (parser, "no type or storage class may be specified here");
      c_parser_objc_protocol_definition (parser, specs->attrs);
      return;
    }
  /* APPLE LOCAL end radar 4947311 - protocol attributes */
  pending_xref_error ();
  prefix_attrs = specs->attrs;
  all_prefix_attrs = prefix_attrs;
  specs->attrs = NULL_TREE;
  while (true)
    {
      struct c_declarator *declarator;
      bool dummy = false;
      tree fnbody;
      /* Declaring either one or more declarators (in which case we
	 should diagnose if there were no declaration specifiers) or a
	 function definition (in which case the diagnostic for
	 implicit int suffices).  */
      declarator = c_parser_declarator (parser, specs->type_seen_p,
					C_DTR_NORMAL, &dummy);
      if (declarator == NULL)
	{
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  return;
	}
      if (c_parser_next_token_is (parser, CPP_EQ)
	  || c_parser_next_token_is (parser, CPP_COMMA)
	  || c_parser_next_token_is (parser, CPP_SEMICOLON)
	  || c_parser_next_token_is_keyword (parser, RID_ASM)
	  /* APPLE LOCAL radar 4708210 (for_objc_collection in 4.2) */
	  || c_parser_next_token_is_keyword (parser, RID_IN)
	  || c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	{
	  tree asm_name = NULL_TREE;
	  tree postfix_attrs = NULL_TREE;
	  if (!diagnosed_no_specs && !specs->declspecs_seen_p)
	    {
	      diagnosed_no_specs = true;
	      pedwarn ("data definition has no type or storage class");
	    }
	  /* Having seen a data definition, there cannot now be a
	     function definition.  */
	  fndef_ok = false;
	  if (c_parser_next_token_is_keyword (parser, RID_ASM))
	    asm_name = c_parser_simple_asm_expr (parser);
	  if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
	    postfix_attrs = c_parser_attributes (parser);
	  /* APPLE LOCAL begin radar 4708210 (for_objc_collection in 4.2) */
	  if (c_parser_next_token_is_keyword (parser, RID_IN))
	    {
	      gcc_assert (foreach_elem);
	      *foreach_elem = start_decl (declarator, specs, true,
					  chainon (postfix_attrs, all_prefix_attrs));
	      if (!*foreach_elem)
		*foreach_elem = error_mark_node;
	      start_init (*foreach_elem, asm_name, global_bindings_p ());	
	      return;
	    }
	  /* APPLE LOCAL end radar 4708210 (for_objc_collection in 4.2) */
	  if (c_parser_next_token_is (parser, CPP_EQ))
	    {
	      tree d;
	      struct c_expr init;
	      c_parser_consume_token (parser);
	      /* The declaration of the variable is in effect while
		 its initializer is parsed.  */
	      d = start_decl (declarator, specs, true,
			      chainon (postfix_attrs, all_prefix_attrs));
	      if (!d)
		d = error_mark_node;
	      start_init (d, asm_name, global_bindings_p ());
	      init = c_parser_initializer (parser);
	      finish_init ();
	      if (d != error_mark_node)
		{
		  maybe_warn_string_init (TREE_TYPE (d), init);
		  finish_decl (d, init.value, asm_name);
		}
	    }
	  else
	    {
	      tree d = start_decl (declarator, specs, false,
				   chainon (postfix_attrs,
					    all_prefix_attrs));
	      if (d)
		finish_decl (d, NULL_TREE, asm_name);
	    }
	  if (c_parser_next_token_is (parser, CPP_COMMA))
	    {
	      c_parser_consume_token (parser);
	      if (c_parser_next_token_is_keyword (parser, RID_ATTRIBUTE))
		all_prefix_attrs = chainon (c_parser_attributes (parser),
					    prefix_attrs);
	      else
		all_prefix_attrs = prefix_attrs;
	      continue;
	    }
	  else if (c_parser_next_token_is (parser, CPP_SEMICOLON))
	    {
	      c_parser_consume_token (parser);
	      return;
	    }
	  else
	    {
	      c_parser_error (parser, "expected %<,%> or %<;%>");
	      c_parser_skip_to_end_of_block_or_statement (parser);
	      return;
	    }
	}
      else if (!fndef_ok)
	{
	  c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, "
			  "%<asm%> or %<__attribute__%>");
	  c_parser_skip_to_end_of_block_or_statement (parser);
	  return;
	}
      /* Function definition (nested or otherwise).  */
      if (nested)
	{
	   /* APPLE LOCAL begin radar 5985368 */
	   if (declarator->declarator && declarator->declarator->kind == cdk_block_pointer)
	     error ("bad definition of a block");
	  else if (pedantic)
	   /* APPLE LOCAL end radar 5985368 */
	    pedwarn ("ISO C forbids nested functions");
	  /* APPLE LOCAL begin nested functions 4258406 4357979 (in 4.2 m) */
	  else if (flag_nested_functions == 0)
	    error ("nested functions are disabled, use -fnested-functions to re-enable");
	  /* APPLE LOCAL end nested functions 4258406 4357979 (in 4.2 m) */

	  push_function_context ();
	}
      if (!start_function (specs, declarator, all_prefix_attrs))
	{
	  /* This can appear in many cases looking nothing like a
	     function definition, so we don't give a more specific
	     error suggesting there was one.  */
	  c_parser_error (parser, "expected %<=%>, %<,%>, %<;%>, %<asm%> "
			  "or %<__attribute__%>");
	  if (nested)
	    pop_function_context ();
	  break;
	}
      /* Parse old-style parameter declarations.  ??? Attributes are
	 not allowed to start declaration specifiers here because of a
	 syntax conflict between a function declaration with attribute
	 suffix and a function definition with an attribute prefix on
	 first old-style parameter declaration.  Following the old
	 parser, they are not accepted on subsequent old-style
	 parameter declarations either.  However, there is no
	 ambiguity after the first declaration, nor indeed on the
	 first as long as we don't allow postfix attributes after a
	 declarator with a nonempty identifier list in a definition;
	 and postfix attributes have never been accepted here in
	 function definitions either.  */
      while (c_parser_next_token_is_not (parser, CPP_EOF)
	     && c_parser_next_token_is_not (parser, CPP_OPEN_BRACE))
	/* APPLE LOCAL radar 4708210 (for_objc_collection in 4.2) */
	c_parser_declaration_or_fndef (parser, false, false, true, false, NULL);
      DECL_SOURCE_LOCATION (current_function_decl)
	= c_parser_peek_token (parser)->location;
      store_parm_decls ();
      fnbody = c_parser_compound_statement (parser);
      if (nested)
	{
	  tree decl = current_function_decl;
	  add_stmt (fnbody);
	  finish_function ();
	  pop_function_context ();
	  add_stmt (build_stmt (DECL_EXPR, decl));
	}
      else
	{
	  add_stmt (fnbody);
	  finish_function ();
	}
      break;
    }
}