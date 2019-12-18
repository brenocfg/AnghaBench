#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ c_token ;
struct TYPE_8__ {int error; } ;
typedef  TYPE_2__ c_parser ;

/* Variables and functions */
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_NAME ; 
 int /*<<< orphan*/  c_parse_error (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (TYPE_2__*) ; 
 int /*<<< orphan*/  c_parser_set_source_position_from_token (TYPE_1__*) ; 

__attribute__((used)) static void
c_parser_error (c_parser *parser, const char *gmsgid)
{
  c_token *token = c_parser_peek_token (parser);
  if (parser->error)
    return;
  parser->error = true;
  if (!gmsgid)
    return;
  /* This diagnostic makes more sense if it is tagged to the line of
     the token we just peeked at.  */
  c_parser_set_source_position_from_token (token);
  c_parse_error (gmsgid,
		 /* Because c_parse_error does not understand
		    CPP_KEYWORD, keywords are treated like
		    identifiers.  */
		 (token->type == CPP_KEYWORD ? CPP_NAME : token->type),
		 token->value);
}