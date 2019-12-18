#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  void* tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_14__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_15__ {void* object_scope; void* qualifying_scope; void* scope; int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
typedef  int /*<<< orphan*/  cp_cv_quals ;

/* Variables and functions */
 int ADDR_EXPR ; 
 scalar_t__ CPP_AND ; 
 scalar_t__ CPP_MULT ; 
 int ERROR_MARK ; 
 int INDIRECT_REF ; 
 scalar_t__ NAMESPACE_DECL ; 
 void* NULL_TREE ; 
 scalar_t__ TREE_CODE (void*) ; 
 int /*<<< orphan*/  TYPE_UNQUALIFIED ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_allow_gnu_extensions_p (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_cv_qualifier_seq_opt (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_error_occurred (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_global_scope_opt (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cp_parser_nested_name_specifier (TYPE_2__*,int,int,int,int) ; 
 int /*<<< orphan*/  cp_parser_parse_definitely (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_parse_tentatively (TYPE_2__*) ; 
 scalar_t__ cp_parser_require (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  error (char*,void*) ; 

__attribute__((used)) static enum tree_code
cp_parser_ptr_operator (cp_parser* parser,
			tree* type,
			cp_cv_quals *cv_quals)
{
  enum tree_code code = ERROR_MARK;
  cp_token *token;

  /* Assume that it's not a pointer-to-member.  */
  *type = NULL_TREE;
  /* And that there are no cv-qualifiers.  */
  *cv_quals = TYPE_UNQUALIFIED;

  /* Peek at the next token.  */
  token = cp_lexer_peek_token (parser->lexer);
  /* If it's a `*' or `&' we have a pointer or reference.  */
  if (token->type == CPP_MULT || token->type == CPP_AND)
    {
      /* Remember which ptr-operator we were processing.  */
      code = (token->type == CPP_AND ? ADDR_EXPR : INDIRECT_REF);

      /* Consume the `*' or `&'.  */
      cp_lexer_consume_token (parser->lexer);

      /* A `*' can be followed by a cv-qualifier-seq, and so can a
	 `&', if we are allowing GNU extensions.  (The only qualifier
	 that can legally appear after `&' is `restrict', but that is
	 enforced during semantic analysis.  */
      if (code == INDIRECT_REF
	  || cp_parser_allow_gnu_extensions_p (parser))
	*cv_quals = cp_parser_cv_qualifier_seq_opt (parser);
    }
  else
    {
      /* Try the pointer-to-member case.  */
      cp_parser_parse_tentatively (parser);
      /* Look for the optional `::' operator.  */
      cp_parser_global_scope_opt (parser,
				  /*current_scope_valid_p=*/false);
      /* Look for the nested-name specifier.  */
      cp_parser_nested_name_specifier (parser,
				       /*typename_keyword_p=*/false,
				       /*check_dependency_p=*/true,
				       /*type_p=*/false,
				       /*is_declaration=*/false);
      /* If we found it, and the next token is a `*', then we are
	 indeed looking at a pointer-to-member operator.  */
      if (!cp_parser_error_occurred (parser)
	  && cp_parser_require (parser, CPP_MULT, "`*'"))
	{
	  /* Indicate that the `*' operator was used.  */
	  code = INDIRECT_REF;

	  if (TREE_CODE (parser->scope) == NAMESPACE_DECL)
	    error ("%qD is a namespace", parser->scope);
	  else
	    {
	      /* The type of which the member is a member is given by the
		 current SCOPE.  */
	      *type = parser->scope;
	      /* The next name will not be qualified.  */
	      parser->scope = NULL_TREE;
	      parser->qualifying_scope = NULL_TREE;
	      parser->object_scope = NULL_TREE;
	      /* Look for the optional cv-qualifier-seq.  */
	      *cv_quals = cp_parser_cv_qualifier_seq_opt (parser);
	    }
	}
      /* If that didn't work we don't have a ptr-operator.  */
      if (!cp_parser_parse_definitely (parser))
	cp_parser_error (parser, "expected ptr-operator");
    }

  return code;
}