#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int flags; scalar_t__ type; } ;
typedef  TYPE_3__ const cpp_token ;
struct TYPE_15__ {int parsing_args; int /*<<< orphan*/  skipping; scalar_t__ in_deferred_pragma; scalar_t__ in_directive; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* line_change ) (TYPE_4__*,TYPE_3__ const*,int) ;} ;
struct TYPE_17__ {scalar_t__ cur_token; int mi_valid; TYPE_2__ state; TYPE_1__ cb; TYPE_3__ const directive_result; scalar_t__ lookaheads; TYPE_7__* cur_run; } ;
typedef  TYPE_4__ cpp_reader ;
struct TYPE_18__ {scalar_t__ limit; scalar_t__ base; } ;

/* Variables and functions */
 int BOL ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_HASH ; 
 scalar_t__ CPP_PADDING ; 
 int PREV_WHITE ; 
 scalar_t__ _cpp_handle_directive (TYPE_4__*,int) ; 
 TYPE_3__ const* _cpp_lex_direct (TYPE_4__*) ; 
 int /*<<< orphan*/  abort () ; 
 TYPE_7__* next_tokenrun (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__ const*,int) ; 

const cpp_token *
_cpp_lex_token (cpp_reader *pfile)
{
  cpp_token *result;

  for (;;)
    {
      if (pfile->cur_token == pfile->cur_run->limit)
	{
	  pfile->cur_run = next_tokenrun (pfile->cur_run);
	  pfile->cur_token = pfile->cur_run->base;
	}
      /* We assume that the current token is somewhere in the current
	 run.  */
      if (pfile->cur_token < pfile->cur_run->base
	  || pfile->cur_token >= pfile->cur_run->limit)
	abort ();

      if (pfile->lookaheads)
	{
	  pfile->lookaheads--;
	  result = pfile->cur_token++;
	}
      else
	result = _cpp_lex_direct (pfile);

      if (result->flags & BOL)
	{
	  /* Is this a directive.  If _cpp_handle_directive returns
	     false, it is an assembler #.  */
	  if (result->type == CPP_HASH
	      /* 6.10.3 p 11: Directives in a list of macro arguments
		 gives undefined behavior.  This implementation
		 handles the directive as normal.  */
	      && pfile->state.parsing_args != 1)
	    {
	      if (_cpp_handle_directive (pfile, result->flags & PREV_WHITE))
		{
		  if (pfile->directive_result.type == CPP_PADDING)
		    continue;
		  result = &pfile->directive_result;
		}
	    }
	  else if (pfile->state.in_deferred_pragma)
	    result = &pfile->directive_result;

	  if (pfile->cb.line_change && !pfile->state.skipping)
	    pfile->cb.line_change (pfile, result, pfile->state.parsing_args);
	}

      /* We don't skip tokens in directives.  */
      if (pfile->state.in_directive || pfile->state.in_deferred_pragma)
	break;

      /* Outside a directive, invalidate controlling macros.  At file
	 EOF, _cpp_lex_direct takes care of popping the buffer, so we never
	 get here and MI optimization works.  */
      pfile->mi_valid = false;

      if (!pfile->state.skipping || result->type == CPP_EOF)
	break;
    }

  return result;
}