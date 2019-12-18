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
typedef  int /*<<< orphan*/  tree ;
struct c_parm {int dummy; } ;
typedef  int /*<<< orphan*/  location_t ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_CLOSE_PAREN ; 
 int /*<<< orphan*/  CPP_ELLIPSIS ; 
 int /*<<< orphan*/  CPP_OPEN_BRACE ; 
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  RID_AT_CATCH ; 
 int /*<<< orphan*/  RID_AT_FINALLY ; 
 int /*<<< orphan*/  RID_AT_TRY ; 
 int /*<<< orphan*/  c_parser_compound_statement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_compound_statement_nostart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct c_parm* c_parser_parameter_declaration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  c_parser_skip_until_found (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  grokparm (struct c_parm*) ; 
 int /*<<< orphan*/  objc_begin_catch_clause (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_begin_try_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_build_finally_clause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objc_finish_catch_clause () ; 
 int /*<<< orphan*/  objc_finish_try_stmt () ; 

__attribute__((used)) static void
c_parser_objc_try_catch_statement (c_parser *parser)
{
  location_t loc;
  tree stmt;
  gcc_assert (c_parser_next_token_is_keyword (parser, RID_AT_TRY));
  c_parser_consume_token (parser);
  loc = c_parser_peek_token (parser)->location;
  stmt = c_parser_compound_statement (parser);
  objc_begin_try_stmt (loc, stmt);
  while (c_parser_next_token_is_keyword (parser, RID_AT_CATCH))
    {
      struct c_parm *parm;
      c_parser_consume_token (parser);
      if (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	break;
      /* APPLE LOCAL begin radar 2848255 */
      if (c_parser_next_token_is (parser, CPP_ELLIPSIS))
	{
	  /* @catch (...) */
	  c_parser_consume_token (parser);
	   c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	   objc_begin_catch_clause (NULL_TREE);
	}
      else
	{
	   parm = c_parser_parameter_declaration (parser, NULL_TREE);
	   if (parm == NULL)
	    {
	      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, NULL);
	      break;
	    }
	   c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
	   objc_begin_catch_clause (grokparm (parm));
	}
      /* APPLE LOCAL end radar 2848255 */
      if (c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
	c_parser_compound_statement_nostart (parser);
      objc_finish_catch_clause ();
    }
  if (c_parser_next_token_is_keyword (parser, RID_AT_FINALLY))
    {
      location_t finloc;
      tree finstmt;
      c_parser_consume_token (parser);
      finloc = c_parser_peek_token (parser)->location;
      finstmt = c_parser_compound_statement (parser);
      objc_build_finally_clause (finloc, finstmt);
    }
  objc_finish_try_stmt ();
}