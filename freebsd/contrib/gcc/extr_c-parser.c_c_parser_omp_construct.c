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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  enum pragma_kind { ____Placeholder_pragma_kind } pragma_kind ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int pragma_kind; int /*<<< orphan*/  location; } ;

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
 int /*<<< orphan*/  c_maybe_initialize_eh () ; 
 int /*<<< orphan*/  c_parser_consume_pragma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_omp_atomic (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_omp_critical (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_omp_for (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_omp_master (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_omp_ordered (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_omp_parallel (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_omp_sections (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_omp_single (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static void
c_parser_omp_construct (c_parser *parser)
{
  enum pragma_kind p_kind;
  location_t loc;
  tree stmt;

  loc = c_parser_peek_token (parser)->location;
  p_kind = c_parser_peek_token (parser)->pragma_kind;
  c_parser_consume_pragma (parser);

  /* For all constructs below except #pragma omp atomic
     MUST_NOT_THROW catch handlers are needed when exceptions
     are enabled.  */
  if (p_kind != PRAGMA_OMP_ATOMIC)
    c_maybe_initialize_eh ();

  switch (p_kind)
    {
    case PRAGMA_OMP_ATOMIC:
      c_parser_omp_atomic (parser);
      return;
    case PRAGMA_OMP_CRITICAL:
      stmt = c_parser_omp_critical (parser);
      break;
    case PRAGMA_OMP_FOR:
      stmt = c_parser_omp_for (parser);
      break;
    case PRAGMA_OMP_MASTER:
      stmt = c_parser_omp_master (parser);
      break;
    case PRAGMA_OMP_ORDERED:
      stmt = c_parser_omp_ordered (parser);
      break;
    case PRAGMA_OMP_PARALLEL:
      stmt = c_parser_omp_parallel (parser);
      break;
    case PRAGMA_OMP_SECTIONS:
      stmt = c_parser_omp_sections (parser);
      break;
    case PRAGMA_OMP_SINGLE:
      stmt = c_parser_omp_single (parser);
      break;
    default:
      gcc_unreachable ();
    }

  if (stmt)
    SET_EXPR_LOCATION (stmt, loc);
}