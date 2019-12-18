#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
typedef  enum pragma_context { ____Placeholder_pragma_context } pragma_context ;
struct TYPE_18__ {scalar_t__ type; unsigned int pragma_kind; } ;
typedef  TYPE_1__ cp_token ;
struct TYPE_19__ {TYPE_16__* lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_17__ {int in_pragma; } ;

/* Variables and functions */
 scalar_t__ CPP_PRAGMA ; 
 unsigned int PRAGMA_FIRST_EXTERNAL ; 
#define  PRAGMA_GCC_PCH_PREPROCESS 142 
#define  PRAGMA_OMP_ATOMIC 141 
#define  PRAGMA_OMP_BARRIER 140 
#define  PRAGMA_OMP_CRITICAL 139 
#define  PRAGMA_OMP_FLUSH 138 
#define  PRAGMA_OMP_FOR 137 
#define  PRAGMA_OMP_MASTER 136 
#define  PRAGMA_OMP_ORDERED 135 
#define  PRAGMA_OMP_PARALLEL 134 
#define  PRAGMA_OMP_SECTION 133 
#define  PRAGMA_OMP_SECTIONS 132 
#define  PRAGMA_OMP_SINGLE 131 
#define  PRAGMA_OMP_THREADPRIVATE 130 
 int /*<<< orphan*/  c_invoke_pragma_handler (unsigned int) ; 
 TYPE_1__* cp_lexer_consume_token (TYPE_16__*) ; 
 int /*<<< orphan*/  cp_parser_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  cp_parser_omp_barrier (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_omp_construct (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_omp_flush (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_omp_threadprivate (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cp_parser_skip_to_pragma_eol (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
#define  pragma_compound 129 
 int pragma_external ; 
#define  pragma_stmt 128 

__attribute__((used)) static bool
cp_parser_pragma (cp_parser *parser, enum pragma_context context)
{
  cp_token *pragma_tok;
  unsigned int id;

  pragma_tok = cp_lexer_consume_token (parser->lexer);
  gcc_assert (pragma_tok->type == CPP_PRAGMA);
  parser->lexer->in_pragma = true;

  id = pragma_tok->pragma_kind;
  switch (id)
    {
    case PRAGMA_GCC_PCH_PREPROCESS:
      error ("%<#pragma GCC pch_preprocess%> must be first");
      break;

    case PRAGMA_OMP_BARRIER:
      switch (context)
	{
	case pragma_compound:
	  cp_parser_omp_barrier (parser, pragma_tok);
	  return false;
	case pragma_stmt:
	  error ("%<#pragma omp barrier%> may only be "
		 "used in compound statements");
	  break;
	default:
	  goto bad_stmt;
	}
      break;

    case PRAGMA_OMP_FLUSH:
      switch (context)
	{
	case pragma_compound:
	  cp_parser_omp_flush (parser, pragma_tok);
	  return false;
	case pragma_stmt:
	  error ("%<#pragma omp flush%> may only be "
		 "used in compound statements");
	  break;
	default:
	  goto bad_stmt;
	}
      break;

    case PRAGMA_OMP_THREADPRIVATE:
      cp_parser_omp_threadprivate (parser, pragma_tok);
      return false;

    case PRAGMA_OMP_ATOMIC:
    case PRAGMA_OMP_CRITICAL:
    case PRAGMA_OMP_FOR:
    case PRAGMA_OMP_MASTER:
    case PRAGMA_OMP_ORDERED:
    case PRAGMA_OMP_PARALLEL:
    case PRAGMA_OMP_SECTIONS:
    case PRAGMA_OMP_SINGLE:
      if (context == pragma_external)
	goto bad_stmt;
      cp_parser_omp_construct (parser, pragma_tok);
      return true;

    case PRAGMA_OMP_SECTION:
      error ("%<#pragma omp section%> may only be used in "
	     "%<#pragma omp sections%> construct");
      break;

    default:
      gcc_assert (id >= PRAGMA_FIRST_EXTERNAL);
      c_invoke_pragma_handler (id);
      break;

    bad_stmt:
      cp_parser_error (parser, "expected declaration specifiers");
      break;
    }

  cp_parser_skip_to_pragma_eol (parser, pragma_tok);
  return false;
}