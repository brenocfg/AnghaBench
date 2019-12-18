#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_18__ {int keyword; } ;
typedef  TYPE_1__ cp_token ;
typedef  int /*<<< orphan*/  cp_parser_flags ;
struct TYPE_19__ {int /*<<< orphan*/  lexer; int /*<<< orphan*/  in_declarator_p; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_20__ {scalar_t__* specs; int conflicting_specifiers_p; int any_specifiers_p; int /*<<< orphan*/  storage_class; int /*<<< orphan*/  attributes; } ;
typedef  TYPE_3__ cp_decl_specifier_seq ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PARSER_FLAGS_NO_USER_DEFINED_TYPES ; 
 int /*<<< orphan*/  CP_PARSER_FLAGS_OPTIONAL ; 
 int RID_ATTRIBUTE ; 
#define  RID_AUTO 138 
#define  RID_EXPLICIT 137 
#define  RID_EXTERN 136 
#define  RID_FRIEND 135 
#define  RID_INLINE 134 
#define  RID_MUTABLE 133 
#define  RID_REGISTER 132 
#define  RID_STATIC 131 
#define  RID_THREAD 130 
#define  RID_TYPEDEF 129 
#define  RID_VIRTUAL 128 
 int /*<<< orphan*/  at_class_scope_p () ; 
 int /*<<< orphan*/  chainon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_decl_specs (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_purge_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_attributes_opt (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_check_decl_spec (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_commit_to_tentative_parse (TYPE_2__*) ; 
 scalar_t__ cp_parser_constructor_declarator_p (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cp_parser_function_specifier_opt (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_set_storage_class (TYPE_2__*,TYPE_3__*,int) ; 
 scalar_t__ cp_parser_type_specifier (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int,int*,int*) ; 
 scalar_t__ ds_friend ; 
 scalar_t__ ds_thread ; 
 scalar_t__ ds_typedef ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  sc_none ; 

__attribute__((used)) static void
cp_parser_decl_specifier_seq (cp_parser* parser,
			      cp_parser_flags flags,
			      cp_decl_specifier_seq *decl_specs,
			      int* declares_class_or_enum)
{
  bool constructor_possible_p = !parser->in_declarator_p;

  /* Clear DECL_SPECS.  */
  clear_decl_specs (decl_specs);

  /* Assume no class or enumeration type is declared.  */
  *declares_class_or_enum = 0;

  /* Keep reading specifiers until there are no more to read.  */
  while (true)
    {
      bool constructor_p;
      bool found_decl_spec;
      cp_token *token;

      /* Peek at the next token.  */
      token = cp_lexer_peek_token (parser->lexer);
      /* Handle attributes.  */
      if (token->keyword == RID_ATTRIBUTE)
	{
	  /* Parse the attributes.  */
	  decl_specs->attributes
	    = chainon (decl_specs->attributes,
		       cp_parser_attributes_opt (parser));
	  continue;
	}
      /* Assume we will find a decl-specifier keyword.  */
      found_decl_spec = true;
      /* If the next token is an appropriate keyword, we can simply
	 add it to the list.  */
      switch (token->keyword)
	{
	  /* decl-specifier:
	       friend  */
	case RID_FRIEND:
	  if (!at_class_scope_p ())
	    {
	      error ("%<friend%> used outside of class");
	      cp_lexer_purge_token (parser->lexer);
	    }
	  else
	    {
	      ++decl_specs->specs[(int) ds_friend];
	      /* Consume the token.  */
	      cp_lexer_consume_token (parser->lexer);
	    }
	  break;

	  /* function-specifier:
	       inline
	       virtual
	       explicit  */
	case RID_INLINE:
	case RID_VIRTUAL:
	case RID_EXPLICIT:
	  cp_parser_function_specifier_opt (parser, decl_specs);
	  break;

	  /* decl-specifier:
	       typedef  */
	case RID_TYPEDEF:
	  ++decl_specs->specs[(int) ds_typedef];
	  /* Consume the token.  */
	  cp_lexer_consume_token (parser->lexer);
	  /* A constructor declarator cannot appear in a typedef.  */
	  constructor_possible_p = false;
	  /* The "typedef" keyword can only occur in a declaration; we
	     may as well commit at this point.  */
	  cp_parser_commit_to_tentative_parse (parser);

          if (decl_specs->storage_class != sc_none)
            decl_specs->conflicting_specifiers_p = true;
	  break;

	  /* storage-class-specifier:
	       auto
	       register
	       static
	       extern
	       mutable

	     GNU Extension:
	       thread  */
	case RID_AUTO:
	case RID_REGISTER:
	case RID_STATIC:
	case RID_EXTERN:
	case RID_MUTABLE:
	  /* Consume the token.  */
	  cp_lexer_consume_token (parser->lexer);
	  cp_parser_set_storage_class (parser, decl_specs, token->keyword);
	  break;
	case RID_THREAD:
	  /* Consume the token.  */
	  cp_lexer_consume_token (parser->lexer);
	  ++decl_specs->specs[(int) ds_thread];
	  break;

	default:
	  /* We did not yet find a decl-specifier yet.  */
	  found_decl_spec = false;
	  break;
	}

      /* Constructors are a special case.  The `S' in `S()' is not a
	 decl-specifier; it is the beginning of the declarator.  */
      constructor_p
	= (!found_decl_spec
	   && constructor_possible_p
	   && (cp_parser_constructor_declarator_p
	       (parser, decl_specs->specs[(int) ds_friend] != 0)));

      /* If we don't have a DECL_SPEC yet, then we must be looking at
	 a type-specifier.  */
      if (!found_decl_spec && !constructor_p)
	{
	  int decl_spec_declares_class_or_enum;
	  bool is_cv_qualifier;
	  tree type_spec;

	  type_spec
	    = cp_parser_type_specifier (parser, flags,
					decl_specs,
					/*is_declaration=*/true,
					&decl_spec_declares_class_or_enum,
					&is_cv_qualifier);

	  *declares_class_or_enum |= decl_spec_declares_class_or_enum;

	  /* If this type-specifier referenced a user-defined type
	     (a typedef, class-name, etc.), then we can't allow any
	     more such type-specifiers henceforth.

	     [dcl.spec]

	     The longest sequence of decl-specifiers that could
	     possibly be a type name is taken as the
	     decl-specifier-seq of a declaration.  The sequence shall
	     be self-consistent as described below.

	     [dcl.type]

	     As a general rule, at most one type-specifier is allowed
	     in the complete decl-specifier-seq of a declaration.  The
	     only exceptions are the following:

	     -- const or volatile can be combined with any other
		type-specifier.

	     -- signed or unsigned can be combined with char, long,
		short, or int.

	     -- ..

	     Example:

	       typedef char* Pc;
	       void g (const int Pc);

	     Here, Pc is *not* part of the decl-specifier seq; it's
	     the declarator.  Therefore, once we see a type-specifier
	     (other than a cv-qualifier), we forbid any additional
	     user-defined types.  We *do* still allow things like `int
	     int' to be considered a decl-specifier-seq, and issue the
	     error message later.  */
	  if (type_spec && !is_cv_qualifier)
	    flags |= CP_PARSER_FLAGS_NO_USER_DEFINED_TYPES;
	  /* A constructor declarator cannot follow a type-specifier.  */
	  if (type_spec)
	    {
	      constructor_possible_p = false;
	      found_decl_spec = true;
	    }
	}

      /* If we still do not have a DECL_SPEC, then there are no more
	 decl-specifiers.  */
      if (!found_decl_spec)
	break;

      decl_specs->any_specifiers_p = true;
      /* After we see one decl-specifier, further decl-specifiers are
	 always optional.  */
      flags |= CP_PARSER_FLAGS_OPTIONAL;
    }

  cp_parser_check_decl_spec (decl_specs);

  /* Don't allow a friend specifier with a class definition.  */
  if (decl_specs->specs[(int) ds_friend] != 0
      && (*declares_class_or_enum & 2))
    error ("class definition may not be declared a friend");
}