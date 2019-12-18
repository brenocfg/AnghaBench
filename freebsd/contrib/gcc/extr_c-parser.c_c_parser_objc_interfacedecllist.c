#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; scalar_t__ keyword; } ;
typedef  TYPE_1__ c_token ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
#define  CPP_EOF 130 
 scalar_t__ CPP_KEYWORD ; 
#define  CPP_PRAGMA 129 
#define  CPP_SEMICOLON 128 
 int /*<<< orphan*/  RID_AT_END ; 
 scalar_t__ RID_AT_PROPERTY ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_declaration_or_fndef (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_objc_methodproto (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_objc_property_declaration (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_pragma (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_token_starts_methodproto (TYPE_1__*) ; 
 int /*<<< orphan*/  pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  pragma_external ; 

__attribute__((used)) static void
/* APPLE LOCAL C* property (Radar 4436866) (in 4.2 b) */
c_parser_objc_interfacedecllist (c_parser *parser)
{
  while (true)
    {
      /* APPLE LOCAL begin C* property (Radar 4436866) (in 4.2 b) */
      c_token *token;
      token = c_parser_peek_token (parser);
      if (token->type == CPP_KEYWORD
	  && token->keyword == RID_AT_PROPERTY)
	{
	  c_parser_objc_property_declaration (parser);
	  continue;
	}
      /* APPLE LOCAL end C* property (Radar 4436866) (in 4.2 b) */
      /* APPLE LOCAL begin C* language (in 4.2 w) */
      if (c_token_starts_methodproto (token))
	{
	  c_parser_objc_methodproto (parser);
	  continue;
	}
      /* APPLE LOCAL end C* language (in 4.2 w) */

      /* The list is terminated by @end.  */
      switch (c_parser_peek_token (parser)->type)
	{
	case CPP_SEMICOLON:
	  if (pedantic)
	    pedwarn ("ISO C does not allow extra %<;%> outside of a function");
	  c_parser_consume_token (parser);
	  break;
      /* APPLE LOCAL begin C* language (in 4.2 w) */
	  /* CPP_PLUS and CPP_MINUS deleted */
      /* APPLE LOCAL end C* language (in 4.2 w) */
	case CPP_PRAGMA:
	  c_parser_pragma (parser, pragma_external);
	  break;
	case CPP_EOF:
	  return;
	default:
	  if (c_parser_next_token_is_keyword (parser, RID_AT_END))
	    return;
	  /* APPLE LOCAL radar 4708210 (for_objc_collection in 4.2) */
	  c_parser_declaration_or_fndef (parser, false, true, false, true, NULL);
	  break;
	}
    }
}