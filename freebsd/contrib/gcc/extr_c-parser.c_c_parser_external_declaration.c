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
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int type; int /*<<< orphan*/  keyword; } ;

/* Variables and functions */
#define  CPP_KEYWORD 141 
#define  CPP_MINUS 140 
#define  CPP_PLUS 139 
#define  CPP_PRAGMA 138 
#define  CPP_SEMICOLON 137 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_ASM 136 
#define  RID_AT_ALIAS 135 
#define  RID_AT_CLASS 134 
#define  RID_AT_END 133 
#define  RID_AT_IMPLEMENTATION 132 
#define  RID_AT_INTERFACE 131 
#define  RID_AT_PROPERTY 130 
#define  RID_AT_PROTOCOL 129 
#define  RID_EXTENSION 128 
 int /*<<< orphan*/  c_dialect_objc () ; 
 int /*<<< orphan*/  c_parser_asm_definition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_declaration_or_fndef (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_alias_declaration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_class_declaration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_class_definition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_method_definition (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_property_declaration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_protocol_definition (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_pragma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int disable_extension_diagnostics () ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_finish_implementation () ; 
 int /*<<< orphan*/  pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  pragma_external ; 
 int /*<<< orphan*/  restore_extension_diagnostics (int) ; 

__attribute__((used)) static void
c_parser_external_declaration (c_parser *parser)
{
  int ext;
  switch (c_parser_peek_token (parser)->type)
    {
    case CPP_KEYWORD:
      switch (c_parser_peek_token (parser)->keyword)
	{
	case RID_EXTENSION:
	  ext = disable_extension_diagnostics ();
	  c_parser_consume_token (parser);
	  c_parser_external_declaration (parser);
	  restore_extension_diagnostics (ext);
	  break;
	case RID_ASM:
	  c_parser_asm_definition (parser);
	  break;
	case RID_AT_INTERFACE:
	case RID_AT_IMPLEMENTATION:
	  gcc_assert (c_dialect_objc ());
	  /* APPLE LOCAL radar 4548636 - class attributes. */
	  c_parser_objc_class_definition (parser, NULL_TREE);
	  break;
	case RID_AT_CLASS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_class_declaration (parser);
	  break;
	case RID_AT_ALIAS:
	  gcc_assert (c_dialect_objc ());
	  c_parser_objc_alias_declaration (parser);
	  break;
	case RID_AT_PROTOCOL:
	  gcc_assert (c_dialect_objc ());
	  /* APPLE LOCAL begin radar 4947311 - protocol attributes */
	  c_parser_objc_protocol_definition (parser, NULL_TREE);
	  break;
	  /* APPLE LOCAL end radar 4947311 - protocol attributes */
	  /* APPLE LOCAL begin C* property (Radar 4436866) (in 4.2 x) */
	case RID_AT_PROPERTY:
	  c_parser_objc_property_declaration (parser);
	  break;
	  /* APPLE LOCAL end C* property (Radar 4436866) (in 4.2 x) */
	case RID_AT_END:
	  gcc_assert (c_dialect_objc ());
	  c_parser_consume_token (parser);
	  objc_finish_implementation ();
	  break;
	default:
	  goto decl_or_fndef;
	}
      break;
    case CPP_SEMICOLON:
      if (pedantic)
	pedwarn ("ISO C does not allow extra %<;%> outside of a function");
      c_parser_consume_token (parser);
      break;
    case CPP_PRAGMA:
      c_parser_pragma (parser, pragma_external);
      break;
    case CPP_PLUS:
    case CPP_MINUS:
      if (c_dialect_objc ())
	{
	  c_parser_objc_method_definition (parser);
	  break;
	}
      /* Else fall through, and yield a syntax error trying to parse
	 as a declaration or function definition.  */
    default:
    decl_or_fndef:
      /* A declaration or a function definition.  We can only tell
	 which after parsing the declaration specifiers, if any, and
	 the first declarator.  */
      /* APPLE LOCAL radar 4708210 (for_objc_collection in 4.2) */
      c_parser_declaration_or_fndef (parser, true, true, false, true, NULL);
      break;
    }
}