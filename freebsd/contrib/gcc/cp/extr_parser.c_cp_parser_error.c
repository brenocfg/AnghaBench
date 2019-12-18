#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ cp_token ;
struct TYPE_12__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_3__ cp_parser ;

/* Variables and functions */
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_NAME ; 
 scalar_t__ CPP_PRAGMA ; 
 int /*<<< orphan*/  c_parse_error (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_set_source_position_from_token (TYPE_2__*) ; 
 int /*<<< orphan*/  cp_parser_simulate_error (TYPE_3__*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_pragma_eol (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void
cp_parser_error (cp_parser* parser, const char* message)
{
  if (!cp_parser_simulate_error (parser))
    {
      cp_token *token = cp_lexer_peek_token (parser->lexer);
      /* This diagnostic makes more sense if it is tagged to the line
	 of the token we just peeked at.  */
      cp_lexer_set_source_position_from_token (token);

      if (token->type == CPP_PRAGMA)
	{
	  error ("%<#pragma%> is not allowed here");
	  cp_parser_skip_to_pragma_eol (parser, token);
	  return;
	}

      c_parse_error (message,
		     /* Because c_parser_error does not understand
			CPP_KEYWORD, keywords are treated like
			identifiers.  */
		     (token->type == CPP_KEYWORD ? CPP_NAME : token->type),
		     token->u.value);
    }
}