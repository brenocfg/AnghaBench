#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ type; scalar_t__ keyword; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_17__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_EQ ; 
 scalar_t__ CPP_GREATER ; 
 scalar_t__ CPP_LESS ; 
 scalar_t__ CPP_NAME ; 
 scalar_t__ CPP_OPEN_BRACE ; 
 scalar_t__ OBJC_IS_AT_KEYWORD (scalar_t__) ; 
 scalar_t__ RID_ATTRIBUTE ; 
 scalar_t__ RID_EXPORT ; 
 scalar_t__ RID_EXTERN ; 
 scalar_t__ RID_INLINE ; 
 scalar_t__ RID_MAX ; 
 scalar_t__ RID_NAMESPACE ; 
 scalar_t__ RID_STATIC ; 
 scalar_t__ RID_TEMPLATE ; 
 scalar_t__ c_dialect_objc () ; 
 TYPE_1__* cp_lexer_peek_nth_token (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_allow_gnu_extensions_p (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_block_declaration (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cp_parser_explicit_instantiation (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_explicit_specialization (TYPE_2__*) ; 
 scalar_t__ cp_parser_extension_opt (TYPE_2__*,int*) ; 
 scalar_t__ cp_parser_is_string_literal (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_linkage_specification (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_namespace_definition (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_objc_declaration (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_template_declaration (TYPE_2__*,int) ; 
 int /*<<< orphan*/  declarator_obstack ; 
 void* obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 
 int pedantic ; 

__attribute__((used)) static void
cp_parser_declaration (cp_parser* parser)
{
  cp_token token1;
  cp_token token2;
  int saved_pedantic;
  void *p;

  /* Check for the `__extension__' keyword.  */
  if (cp_parser_extension_opt (parser, &saved_pedantic))
    {
      /* Parse the qualified declaration.  */
      cp_parser_declaration (parser);
      /* Restore the PEDANTIC flag.  */
      pedantic = saved_pedantic;

      return;
    }

  /* Try to figure out what kind of declaration is present.  */
  token1 = *cp_lexer_peek_token (parser->lexer);

  if (token1.type != CPP_EOF)
    token2 = *cp_lexer_peek_nth_token (parser->lexer, 2);
  else
    {
      token2.type = CPP_EOF;
      token2.keyword = RID_MAX;
    }

  /* Get the high-water mark for the DECLARATOR_OBSTACK.  */
  p = obstack_alloc (&declarator_obstack, 0);

  /* If the next token is `extern' and the following token is a string
     literal, then we have a linkage specification.  */
  if (token1.keyword == RID_EXTERN
      && cp_parser_is_string_literal (&token2))
    cp_parser_linkage_specification (parser);
  /* If the next token is `template', then we have either a template
     declaration, an explicit instantiation, or an explicit
     specialization.  */
  else if (token1.keyword == RID_TEMPLATE)
    {
      /* `template <>' indicates a template specialization.  */
      if (token2.type == CPP_LESS
	  && cp_lexer_peek_nth_token (parser->lexer, 3)->type == CPP_GREATER)
	cp_parser_explicit_specialization (parser);
      /* `template <' indicates a template declaration.  */
      else if (token2.type == CPP_LESS)
	cp_parser_template_declaration (parser, /*member_p=*/false);
      /* Anything else must be an explicit instantiation.  */
      else
	cp_parser_explicit_instantiation (parser);
    }
  /* If the next token is `export', then we have a template
     declaration.  */
  else if (token1.keyword == RID_EXPORT)
    cp_parser_template_declaration (parser, /*member_p=*/false);
  /* If the next token is `extern', 'static' or 'inline' and the one
     after that is `template', we have a GNU extended explicit
     instantiation directive.  */
  else if (cp_parser_allow_gnu_extensions_p (parser)
	   && (token1.keyword == RID_EXTERN
	       || token1.keyword == RID_STATIC
	       || token1.keyword == RID_INLINE)
	   && token2.keyword == RID_TEMPLATE)
    cp_parser_explicit_instantiation (parser);
  /* If the next token is `namespace', check for a named or unnamed
     namespace definition.  */
  else if (token1.keyword == RID_NAMESPACE
	   && (/* A named namespace definition.  */
	       (token2.type == CPP_NAME
		&& (cp_lexer_peek_nth_token (parser->lexer, 3)->type
		    != CPP_EQ))
	       /* An unnamed namespace definition.  */
	       || token2.type == CPP_OPEN_BRACE
	       || token2.keyword == RID_ATTRIBUTE))
    cp_parser_namespace_definition (parser);
  /* Objective-C++ declaration/definition.  */
  else if (c_dialect_objc () && OBJC_IS_AT_KEYWORD (token1.keyword))
    cp_parser_objc_declaration (parser);
  /* We must have either a block declaration or a function
     definition.  */
  else
    /* Try to parse a block-declaration, or a function-definition.  */
    cp_parser_block_declaration (parser, /*statement_p=*/false);

  /* Free any declarators allocated.  */
  obstack_free (&declarator_obstack, p);
}