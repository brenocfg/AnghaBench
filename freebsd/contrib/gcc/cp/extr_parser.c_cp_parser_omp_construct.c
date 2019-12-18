#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_11__ {int pragma_kind; int /*<<< orphan*/  location; } ;
typedef  TYPE_1__ cp_token ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
#define  PRAGMA_OMP_ATOMIC 135 
#define  PRAGMA_OMP_CRITICAL 134 
#define  PRAGMA_OMP_FOR 133 
#define  PRAGMA_OMP_MASTER 132 
#define  PRAGMA_OMP_ORDERED 131 
#define  PRAGMA_OMP_PARALLEL 130 
#define  PRAGMA_OMP_SECTIONS 129 
#define  PRAGMA_OMP_SINGLE 128 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_omp_atomic (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cp_parser_omp_critical (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cp_parser_omp_for (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cp_parser_omp_master (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cp_parser_omp_ordered (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cp_parser_omp_parallel (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cp_parser_omp_sections (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ cp_parser_omp_single (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static void
cp_parser_omp_construct (cp_parser *parser, cp_token *pragma_tok)
{
  tree stmt;

  switch (pragma_tok->pragma_kind)
    {
    case PRAGMA_OMP_ATOMIC:
      cp_parser_omp_atomic (parser, pragma_tok);
      return;
    case PRAGMA_OMP_CRITICAL:
      stmt = cp_parser_omp_critical (parser, pragma_tok);
      break;
    case PRAGMA_OMP_FOR:
      stmt = cp_parser_omp_for (parser, pragma_tok);
      break;
    case PRAGMA_OMP_MASTER:
      stmt = cp_parser_omp_master (parser, pragma_tok);
      break;
    case PRAGMA_OMP_ORDERED:
      stmt = cp_parser_omp_ordered (parser, pragma_tok);
      break;
    case PRAGMA_OMP_PARALLEL:
      stmt = cp_parser_omp_parallel (parser, pragma_tok);
      break;
    case PRAGMA_OMP_SECTIONS:
      stmt = cp_parser_omp_sections (parser, pragma_tok);
      break;
    case PRAGMA_OMP_SINGLE:
      stmt = cp_parser_omp_single (parser, pragma_tok);
      break;
    default:
      gcc_unreachable ();
    }

  if (stmt)
    SET_EXPR_LOCATION (stmt, pragma_tok->location);
}