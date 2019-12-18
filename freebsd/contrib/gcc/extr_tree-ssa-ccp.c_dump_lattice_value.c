#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int lattice_val; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ prop_value_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  CONSTANT 132 
#define  UNDEFINED 131 
#define  UNINITIALIZED 130 
#define  UNKNOWN_VAL 129 
#define  VARYING 128 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_lattice_value (FILE *outf, const char *prefix, prop_value_t val)
{
  switch (val.lattice_val)
    {
    case UNINITIALIZED:
      fprintf (outf, "%sUNINITIALIZED", prefix);
      break;
    case UNDEFINED:
      fprintf (outf, "%sUNDEFINED", prefix);
      break;
    case VARYING:
      fprintf (outf, "%sVARYING", prefix);
      break;
    case UNKNOWN_VAL:
      fprintf (outf, "%sUNKNOWN_VAL", prefix);
      break;
    case CONSTANT:
      fprintf (outf, "%sCONSTANT ", prefix);
      print_generic_expr (outf, val.value, dump_flags);
      break;
    default:
      gcc_unreachable ();
    }
}