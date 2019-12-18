#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 int OMP_CLAUSE_CODE (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_COPYIN 148 
#define  OMP_CLAUSE_COPYPRIVATE 147 
 int /*<<< orphan*/  OMP_CLAUSE_DECL (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_DEFAULT 146 
 int /*<<< orphan*/  OMP_CLAUSE_DEFAULT_KIND (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_DEFAULT_NONE 145 
#define  OMP_CLAUSE_DEFAULT_PRIVATE 144 
#define  OMP_CLAUSE_DEFAULT_SHARED 143 
#define  OMP_CLAUSE_DEFAULT_UNSPECIFIED 142 
#define  OMP_CLAUSE_FIRSTPRIVATE 141 
#define  OMP_CLAUSE_IF 140 
 int /*<<< orphan*/  OMP_CLAUSE_IF_EXPR (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_LASTPRIVATE 139 
#define  OMP_CLAUSE_NOWAIT 138 
#define  OMP_CLAUSE_NUM_THREADS 137 
 int /*<<< orphan*/  OMP_CLAUSE_NUM_THREADS_EXPR (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_ORDERED 136 
#define  OMP_CLAUSE_PRIVATE 135 
#define  OMP_CLAUSE_REDUCTION 134 
 int /*<<< orphan*/  OMP_CLAUSE_REDUCTION_CODE (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_SCHEDULE 133 
 int /*<<< orphan*/  OMP_CLAUSE_SCHEDULE_CHUNK_EXPR (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_SCHEDULE_DYNAMIC 132 
#define  OMP_CLAUSE_SCHEDULE_GUIDED 131 
 int /*<<< orphan*/  OMP_CLAUSE_SCHEDULE_KIND (int /*<<< orphan*/ ) ; 
#define  OMP_CLAUSE_SCHEDULE_RUNTIME 130 
#define  OMP_CLAUSE_SCHEDULE_STATIC 129 
#define  OMP_CLAUSE_SHARED 128 
 int /*<<< orphan*/  dump_generic_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char* op_symbol_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
dump_omp_clause (pretty_printer *buffer, tree clause, int spc, int flags)
{
  const char *name;

  switch (OMP_CLAUSE_CODE (clause))
    {
    case OMP_CLAUSE_PRIVATE:
      name = "private";
      goto print_remap;
    case OMP_CLAUSE_SHARED:
      name = "shared";
      goto print_remap;
    case OMP_CLAUSE_FIRSTPRIVATE:
      name = "firstprivate";
      goto print_remap;
    case OMP_CLAUSE_LASTPRIVATE:
      name = "lastprivate";
      goto print_remap;
    case OMP_CLAUSE_COPYIN:
      name = "copyin";
      goto print_remap;
    case OMP_CLAUSE_COPYPRIVATE:
      name = "copyprivate";
      goto print_remap;
  print_remap:
      pp_string (buffer, name);
      pp_character (buffer, '(');
      dump_generic_node (buffer, OMP_CLAUSE_DECL (clause),
	  spc, flags, false);
      pp_character (buffer, ')');
      break;

    case OMP_CLAUSE_REDUCTION:
      pp_string (buffer, "reduction(");
      pp_string (buffer, op_symbol_1 (OMP_CLAUSE_REDUCTION_CODE (clause)));
      pp_character (buffer, ':');
      dump_generic_node (buffer, OMP_CLAUSE_DECL (clause),
	  spc, flags, false);
      pp_character (buffer, ')');
      break;

    case OMP_CLAUSE_IF:
      pp_string (buffer, "if(");
      dump_generic_node (buffer, OMP_CLAUSE_IF_EXPR (clause),
	  spc, flags, false);
      pp_character (buffer, ')');
      break;

    case OMP_CLAUSE_NUM_THREADS:
      pp_string (buffer, "num_threads(");
      dump_generic_node (buffer, OMP_CLAUSE_NUM_THREADS_EXPR (clause),
	  spc, flags, false);
      pp_character (buffer, ')');
      break;

    case OMP_CLAUSE_NOWAIT:
      pp_string (buffer, "nowait");
      break;
    case OMP_CLAUSE_ORDERED:
      pp_string (buffer, "ordered");
      break;

    case OMP_CLAUSE_DEFAULT:
      pp_string (buffer, "default(");
      switch (OMP_CLAUSE_DEFAULT_KIND (clause))
	{
      case OMP_CLAUSE_DEFAULT_UNSPECIFIED:
	break;
      case OMP_CLAUSE_DEFAULT_SHARED:
	pp_string (buffer, "shared");
	break;
      case OMP_CLAUSE_DEFAULT_NONE:
	pp_string (buffer, "none");
	break;
      case OMP_CLAUSE_DEFAULT_PRIVATE:
	pp_string (buffer, "private");
	break;
      default:
	gcc_unreachable ();
	}
      pp_character (buffer, ')');
      break;

    case OMP_CLAUSE_SCHEDULE:
      pp_string (buffer, "schedule(");
      switch (OMP_CLAUSE_SCHEDULE_KIND (clause))
	{
      case OMP_CLAUSE_SCHEDULE_STATIC:
	pp_string (buffer, "static");
	break;
      case OMP_CLAUSE_SCHEDULE_DYNAMIC:
	pp_string (buffer, "dynamic");
	break;
      case OMP_CLAUSE_SCHEDULE_GUIDED:
	pp_string (buffer, "guided");
	break;
      case OMP_CLAUSE_SCHEDULE_RUNTIME:
	pp_string (buffer, "runtime");
	break;
      default:
	gcc_unreachable ();
	}
      if (OMP_CLAUSE_SCHEDULE_CHUNK_EXPR (clause))
	{
	  pp_character (buffer, ',');
	  dump_generic_node (buffer,
	      OMP_CLAUSE_SCHEDULE_CHUNK_EXPR (clause),
	      spc, flags, false);
	}
      pp_character (buffer, ')');
      break;

    default:
      /* Should never happen.  */
      dump_generic_node (buffer, clause, spc, flags, false);
      break;
    }
}