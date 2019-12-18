#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  cp_parser ;
typedef  int /*<<< orphan*/  cp_declarator ;
struct TYPE_5__ {int /*<<< orphan*/  attributes; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cp_decl_specifier_seq ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PARSER_DECLARATOR_NAMED ; 
 int /*<<< orphan*/  CP_PARSER_FLAGS_OPTIONAL ; 
 int /*<<< orphan*/  NORMAL ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  RID_TEMPLATE ; 
 int /*<<< orphan*/  begin_explicit_instantiation () ; 
 scalar_t__ check_tag_decl (TYPE_1__*) ; 
 int /*<<< orphan*/ * cp_error_declarator ; 
 scalar_t__ cp_parser_allow_gnu_extensions_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_check_for_definition_in_return_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_consume_semicolon_at_end_of_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_decl_specifier_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 int /*<<< orphan*/ * cp_parser_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ cp_parser_declares_only_class_p (int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_function_specifier_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_require_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_end_of_statement (int /*<<< orphan*/ *) ; 
 scalar_t__ cp_parser_storage_class_specifier_opt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dk_no_check ; 
 int /*<<< orphan*/  do_decl_instantiation (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_type_instantiation (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_explicit_instantiation () ; 
 scalar_t__ grokdeclarator (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop_deferring_access_checks () ; 
 int /*<<< orphan*/  push_deferring_access_checks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tf_error ; 

__attribute__((used)) static void
cp_parser_explicit_instantiation (cp_parser* parser)
{
  int declares_class_or_enum;
  cp_decl_specifier_seq decl_specifiers;
  tree extension_specifier = NULL_TREE;

  /* Look for an (optional) storage-class-specifier or
     function-specifier.  */
  if (cp_parser_allow_gnu_extensions_p (parser))
    {
      extension_specifier
	= cp_parser_storage_class_specifier_opt (parser);
      if (!extension_specifier)
	extension_specifier
	  = cp_parser_function_specifier_opt (parser,
					      /*decl_specs=*/NULL);
    }

  /* Look for the `template' keyword.  */
  cp_parser_require_keyword (parser, RID_TEMPLATE, "`template'");
  /* Let the front end know that we are processing an explicit
     instantiation.  */
  begin_explicit_instantiation ();
  /* [temp.explicit] says that we are supposed to ignore access
     control while processing explicit instantiation directives.  */
  push_deferring_access_checks (dk_no_check);
  /* Parse a decl-specifier-seq.  */
  cp_parser_decl_specifier_seq (parser,
				CP_PARSER_FLAGS_OPTIONAL,
				&decl_specifiers,
				&declares_class_or_enum);
  /* If there was exactly one decl-specifier, and it declared a class,
     and there's no declarator, then we have an explicit type
     instantiation.  */
  if (declares_class_or_enum && cp_parser_declares_only_class_p (parser))
    {
      tree type;

      type = check_tag_decl (&decl_specifiers);
      /* Turn access control back on for names used during
	 template instantiation.  */
      pop_deferring_access_checks ();
      if (type)
	do_type_instantiation (type, extension_specifier,
			       /*complain=*/tf_error);
    }
  else
    {
      cp_declarator *declarator;
      tree decl;

      /* Parse the declarator.  */
      declarator
	= cp_parser_declarator (parser, CP_PARSER_DECLARATOR_NAMED,
				/*ctor_dtor_or_conv_p=*/NULL,
				/*parenthesized_p=*/NULL,
				/*member_p=*/false);
      if (declares_class_or_enum & 2)
	cp_parser_check_for_definition_in_return_type (declarator,
						       decl_specifiers.type);
      if (declarator != cp_error_declarator)
	{
	  decl = grokdeclarator (declarator, &decl_specifiers,
				 NORMAL, 0, &decl_specifiers.attributes);
	  /* Turn access control back on for names used during
	     template instantiation.  */
	  pop_deferring_access_checks ();
	  /* Do the explicit instantiation.  */
	  do_decl_instantiation (decl, extension_specifier);
	}
      else
	{
	  pop_deferring_access_checks ();
	  /* Skip the body of the explicit instantiation.  */
	  cp_parser_skip_to_end_of_statement (parser);
	}
    }
  /* We're done with the instantiation.  */
  end_explicit_instantiation ();

  cp_parser_consume_semicolon_at_end_of_statement (parser);
}