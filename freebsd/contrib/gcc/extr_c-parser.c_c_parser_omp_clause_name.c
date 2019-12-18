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
typedef  scalar_t__ pragma_omp_clause ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_NAME ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_COPYIN ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_COPYPRIVATE ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_DEFAULT ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_FIRSTPRIVATE ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_IF ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_LASTPRIVATE ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_NONE ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_NOWAIT ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_NUM_THREADS ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_ORDERED ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_PRIVATE ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_REDUCTION ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_SCHEDULE ; 
 scalar_t__ PRAGMA_OMP_CLAUSE_SHARED ; 
 int /*<<< orphan*/  RID_DEFAULT ; 
 int /*<<< orphan*/  RID_IF ; 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 scalar_t__ c_parser_next_token_is (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ c_parser_next_token_is_keyword (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static pragma_omp_clause
c_parser_omp_clause_name (c_parser *parser)
{
  pragma_omp_clause result = PRAGMA_OMP_CLAUSE_NONE;

  if (c_parser_next_token_is_keyword (parser, RID_IF))
    result = PRAGMA_OMP_CLAUSE_IF;
  else if (c_parser_next_token_is_keyword (parser, RID_DEFAULT))
    result = PRAGMA_OMP_CLAUSE_DEFAULT;
  else if (c_parser_next_token_is (parser, CPP_NAME))
    {
      const char *p = IDENTIFIER_POINTER (c_parser_peek_token (parser)->value);

      switch (p[0])
	{
	case 'c':
	  if (!strcmp ("copyin", p))
	    result = PRAGMA_OMP_CLAUSE_COPYIN;
          else if (!strcmp ("copyprivate", p))
	    result = PRAGMA_OMP_CLAUSE_COPYPRIVATE;
	  break;
	case 'f':
	  if (!strcmp ("firstprivate", p))
	    result = PRAGMA_OMP_CLAUSE_FIRSTPRIVATE;
	  break;
	case 'l':
	  if (!strcmp ("lastprivate", p))
	    result = PRAGMA_OMP_CLAUSE_LASTPRIVATE;
	  break;
	case 'n':
	  if (!strcmp ("nowait", p))
	    result = PRAGMA_OMP_CLAUSE_NOWAIT;
	  else if (!strcmp ("num_threads", p))
	    result = PRAGMA_OMP_CLAUSE_NUM_THREADS;
	  break;
	case 'o':
	  if (!strcmp ("ordered", p))
	    result = PRAGMA_OMP_CLAUSE_ORDERED;
	  break;
	case 'p':
	  if (!strcmp ("private", p))
	    result = PRAGMA_OMP_CLAUSE_PRIVATE;
	  break;
	case 'r':
	  if (!strcmp ("reduction", p))
	    result = PRAGMA_OMP_CLAUSE_REDUCTION;
	  break;
	case 's':
	  if (!strcmp ("schedule", p))
	    result = PRAGMA_OMP_CLAUSE_SCHEDULE;
	  else if (!strcmp ("shared", p))
	    result = PRAGMA_OMP_CLAUSE_SHARED;
	  break;
	}
    }

  if (result != PRAGMA_OMP_CLAUSE_NONE)
    c_parser_consume_token (parser);

  return result;
}