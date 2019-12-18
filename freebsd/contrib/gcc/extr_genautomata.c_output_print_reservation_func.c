#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_8__ {int insn_num; int /*<<< orphan*/  regexp; } ;
struct TYPE_7__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_6__ {scalar_t__ mode; } ;

/* Variables and functions */
 char* ADVANCE_CYCLE_VALUE_NAME ; 
 TYPE_4__* DECL_INSN_RESERV (TYPE_1__*) ; 
 char* DFA_INSN_CODE_FUNC_NAME ; 
 char* FILE_PARAMETER_NAME ; 
 char* INSN_PARAMETER_NAME ; 
 char* INTERNAL_INSN_CODE_NAME ; 
 char* NOTHING_NAME ; 
 char* PRINT_RESERVATION_FUNC_NAME ; 
 TYPE_1__* advance_cycle_insn_decl ; 
 TYPE_2__* description ; 
 scalar_t__ dm_insn_reserv ; 
 int /*<<< orphan*/  finish_regexp_representation () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  output_file ; 
 char* regexp_representation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
output_print_reservation_func (void)
{
  decl_t decl;
  int i, j;

  fprintf (output_file,
	   "void\n%s (FILE *%s, rtx %s ATTRIBUTE_UNUSED)\n{\n",
           PRINT_RESERVATION_FUNC_NAME, FILE_PARAMETER_NAME,
           INSN_PARAMETER_NAME);

  if (DECL_INSN_RESERV (advance_cycle_insn_decl)->insn_num == 0)
    {
      fprintf (output_file, "  fputs (\"%s\", %s);\n}\n\n",
	       NOTHING_NAME, FILE_PARAMETER_NAME);
      return;
    }


  fputs ("  static const char *const reservation_names[] =\n    {",
	 output_file);

  for (i = 0, j = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_insn_reserv && decl != advance_cycle_insn_decl)
	{
	  gcc_assert (j == DECL_INSN_RESERV (decl)->insn_num);
	  j++;
	  
	  fprintf (output_file, "\n      \"%s\",",
		   regexp_representation (DECL_INSN_RESERV (decl)->regexp));
	  finish_regexp_representation ();
	}
    }
  gcc_assert (j == DECL_INSN_RESERV (advance_cycle_insn_decl)->insn_num);

  fprintf (output_file, "\n      \"%s\"\n    };\n  int %s;\n\n",
	   NOTHING_NAME, INTERNAL_INSN_CODE_NAME);

  fprintf (output_file, "  if (%s == 0)\n    %s = %s;\n",
	   INSN_PARAMETER_NAME,
	   INTERNAL_INSN_CODE_NAME, ADVANCE_CYCLE_VALUE_NAME);
  fprintf (output_file, "  else\n\
    {\n\
      %s = %s (%s);\n\
      if (%s > %s)\n\
        %s = %s;\n\
    }\n",
	   INTERNAL_INSN_CODE_NAME, DFA_INSN_CODE_FUNC_NAME,
	       INSN_PARAMETER_NAME,
	   INTERNAL_INSN_CODE_NAME, ADVANCE_CYCLE_VALUE_NAME,
	   INTERNAL_INSN_CODE_NAME, ADVANCE_CYCLE_VALUE_NAME);

  fprintf (output_file, "  fputs (reservation_names[%s], %s);\n}\n\n",
	   INTERNAL_INSN_CODE_NAME, FILE_PARAMETER_NAME);
}