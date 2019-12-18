#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  node; } ;
struct TYPE_20__ {int type; TYPE_1__ val; } ;
typedef  TYPE_4__ cpp_token ;
struct TYPE_19__ {int va_args_ok; } ;
struct TYPE_18__ {int /*<<< orphan*/  n__VA_ARGS__; } ;
struct TYPE_21__ {TYPE_3__ state; TYPE_2__ spec_nodes; } ;
typedef  TYPE_5__ cpp_reader ;
struct TYPE_22__ {int variadic; int /*<<< orphan*/  paramc; } ;
typedef  TYPE_6__ cpp_macro ;

/* Variables and functions */
#define  CPP_CLOSE_PAREN 132 
#define  CPP_COMMA 131 
 int CPP_COMMENT ; 
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
#define  CPP_ELLIPSIS 130 
#define  CPP_EOF 129 
#define  CPP_NAME 128 
 int /*<<< orphan*/  CPP_OPTION (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* _cpp_lex_token (TYPE_5__*) ; 
 int /*<<< orphan*/  _cpp_save_parameter (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c99 ; 
 int /*<<< orphan*/  cpp_error (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpp_token_as_text (TYPE_5__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  discard_comments_in_macro_exp ; 
 int /*<<< orphan*/  pedantic ; 
 int /*<<< orphan*/  warn_variadic_macros ; 

__attribute__((used)) static bool
parse_params (cpp_reader *pfile, cpp_macro *macro)
{
  unsigned int prev_ident = 0;

  for (;;)
    {
      const cpp_token *token = _cpp_lex_token (pfile);

      switch (token->type)
	{
	default:
	  /* Allow/ignore comments in parameter lists if we are
	     preserving comments in macro expansions.  */
	  if (token->type == CPP_COMMENT
	      && ! CPP_OPTION (pfile, discard_comments_in_macro_exp))
	    continue;

	  cpp_error (pfile, CPP_DL_ERROR,
		     "\"%s\" may not appear in macro parameter list",
		     cpp_token_as_text (pfile, token));
	  return false;

	case CPP_NAME:
	  if (prev_ident)
	    {
	      cpp_error (pfile, CPP_DL_ERROR,
			 "macro parameters must be comma-separated");
	      return false;
	    }
	  prev_ident = 1;

	  if (_cpp_save_parameter (pfile, macro, token->val.node))
	    return false;
	  continue;

	case CPP_CLOSE_PAREN:
	  if (prev_ident || macro->paramc == 0)
	    return true;

	  /* Fall through to pick up the error.  */
	case CPP_COMMA:
	  if (!prev_ident)
	    {
	      cpp_error (pfile, CPP_DL_ERROR, "parameter name missing");
	      return false;
	    }
	  prev_ident = 0;
	  continue;

	case CPP_ELLIPSIS:
	  macro->variadic = 1;
	  if (!prev_ident)
	    {
	      _cpp_save_parameter (pfile, macro,
				   pfile->spec_nodes.n__VA_ARGS__);
	      pfile->state.va_args_ok = 1;
	      if (! CPP_OPTION (pfile, c99)
		  && CPP_OPTION (pfile, pedantic)
		  && CPP_OPTION (pfile, warn_variadic_macros))
		cpp_error (pfile, CPP_DL_PEDWARN,
			   "anonymous variadic macros were introduced in C99");
	    }
	  else if (CPP_OPTION (pfile, pedantic)
		   && CPP_OPTION (pfile, warn_variadic_macros))
	    cpp_error (pfile, CPP_DL_PEDWARN,
		       "ISO C does not permit named variadic macros");

	  /* We're at the end, and just expect a closing parenthesis.  */
	  token = _cpp_lex_token (pfile);
	  if (token->type == CPP_CLOSE_PAREN)
	    return true;
	  /* Fall through.  */

	case CPP_EOF:
	  cpp_error (pfile, CPP_DL_ERROR, "missing ')' in macro parameter list");
	  return false;
	}
    }
}