#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  int pragma_omp_clause ;
struct TYPE_20__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_1__ c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_PRAGMA_EOL ; 
#define  PRAGMA_OMP_CLAUSE_COPYIN 140 
#define  PRAGMA_OMP_CLAUSE_COPYPRIVATE 139 
#define  PRAGMA_OMP_CLAUSE_DEFAULT 138 
#define  PRAGMA_OMP_CLAUSE_FIRSTPRIVATE 137 
#define  PRAGMA_OMP_CLAUSE_IF 136 
#define  PRAGMA_OMP_CLAUSE_LASTPRIVATE 135 
#define  PRAGMA_OMP_CLAUSE_NOWAIT 134 
#define  PRAGMA_OMP_CLAUSE_NUM_THREADS 133 
#define  PRAGMA_OMP_CLAUSE_ORDERED 132 
#define  PRAGMA_OMP_CLAUSE_PRIVATE 131 
#define  PRAGMA_OMP_CLAUSE_REDUCTION 130 
#define  PRAGMA_OMP_CLAUSE_SCHEDULE 129 
#define  PRAGMA_OMP_CLAUSE_SHARED 128 
 int /*<<< orphan*/ * c_finish_omp_clauses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_error (TYPE_1__*,char*) ; 
 scalar_t__ c_parser_next_token_is_not (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_copyin (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_copyprivate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_default (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_firstprivate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_if (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_lastprivate (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int c_parser_omp_clause_name (TYPE_1__*) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_nowait (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_num_threads (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_ordered (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_private (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_reduction (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_schedule (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_parser_omp_clause_shared (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_to_pragma_eol (TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*,char const*,char const*) ; 

__attribute__((used)) static tree
c_parser_omp_all_clauses (c_parser *parser, unsigned int mask,
			  const char *where)
{
  tree clauses = NULL;

  while (c_parser_next_token_is_not (parser, CPP_PRAGMA_EOL))
    {
      const pragma_omp_clause c_kind = c_parser_omp_clause_name (parser);
      const char *c_name;
      tree prev = clauses;

      switch (c_kind)
	{
	case PRAGMA_OMP_CLAUSE_COPYIN:
	  clauses = c_parser_omp_clause_copyin (parser, clauses);
	  c_name = "copyin";
	  break;
	case PRAGMA_OMP_CLAUSE_COPYPRIVATE:
	  clauses = c_parser_omp_clause_copyprivate (parser, clauses);
	  c_name = "copyprivate";
	  break;
	case PRAGMA_OMP_CLAUSE_DEFAULT:
	  clauses = c_parser_omp_clause_default (parser, clauses);
	  c_name = "default";
	  break;
	case PRAGMA_OMP_CLAUSE_FIRSTPRIVATE:
	  clauses = c_parser_omp_clause_firstprivate (parser, clauses);
	  c_name = "firstprivate";
	  break;
	case PRAGMA_OMP_CLAUSE_IF:
	  clauses = c_parser_omp_clause_if (parser, clauses);
	  c_name = "if";
	  break;
	case PRAGMA_OMP_CLAUSE_LASTPRIVATE:
	  clauses = c_parser_omp_clause_lastprivate (parser, clauses);
	  c_name = "lastprivate";
	  break;
	case PRAGMA_OMP_CLAUSE_NOWAIT:
	  clauses = c_parser_omp_clause_nowait (parser, clauses);
	  c_name = "nowait";
	  break;
	case PRAGMA_OMP_CLAUSE_NUM_THREADS:
	  clauses = c_parser_omp_clause_num_threads (parser, clauses);
	  c_name = "num_threads";
	  break;
	case PRAGMA_OMP_CLAUSE_ORDERED:
	  clauses = c_parser_omp_clause_ordered (parser, clauses);
	  c_name = "ordered";
	  break;
	case PRAGMA_OMP_CLAUSE_PRIVATE:
	  clauses = c_parser_omp_clause_private (parser, clauses);
	  c_name = "private";
	  break;
	case PRAGMA_OMP_CLAUSE_REDUCTION:
	  clauses = c_parser_omp_clause_reduction (parser, clauses);
	  c_name = "reduction";
	  break;
	case PRAGMA_OMP_CLAUSE_SCHEDULE:
	  clauses = c_parser_omp_clause_schedule (parser, clauses);
	  c_name = "schedule";
	  break;
	case PRAGMA_OMP_CLAUSE_SHARED:
	  clauses = c_parser_omp_clause_shared (parser, clauses);
	  c_name = "shared";
	  break;
	default:
	  c_parser_error (parser, "expected %<#pragma omp%> clause");
	  goto saw_error;
	}

      if (((mask >> c_kind) & 1) == 0 && !parser->error)
	{
	  /* Remove the invalid clause(s) from the list to avoid
	     confusing the rest of the compiler.  */
	  clauses = prev;
	  error ("%qs is not valid for %qs", c_name, where);
	}
    }

 saw_error:
  c_parser_skip_to_pragma_eol (parser);

  return c_finish_omp_clauses (clauses);
}