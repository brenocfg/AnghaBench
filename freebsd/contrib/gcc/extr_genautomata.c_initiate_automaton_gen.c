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

/* Variables and functions */
 char* NDFA_OPTION ; 
 char* NO_MINIMIZATION_OPTION ; 
 char* PROGRESS_OPTION ; 
 char const* STANDARD_OUTPUT_DESCRIPTION_FILE_SUFFIX ; 
 char* TIME_OPTION ; 
 char* V_OPTION ; 
 char* W_OPTION ; 
 char* base_file_name (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 char const* file_name_suffix (char const*) ; 
 int /*<<< orphan*/  initiate_automaton_decl_table () ; 
 int /*<<< orphan*/  initiate_decl_table () ; 
 int /*<<< orphan*/  initiate_insn_decl_table () ; 
 int /*<<< orphan*/  irp ; 
 int ndfa_flag ; 
 int no_minimization_flag ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  obstack_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * output_description_file ; 
 int /*<<< orphan*/  output_description_file_name ; 
 int /*<<< orphan*/  output_file ; 
 int progress_flag ; 
 scalar_t__ split_argument ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 int time_flag ; 
 int v_flag ; 
 int w_flag ; 

__attribute__((used)) static void
initiate_automaton_gen (int argc, char **argv)
{
  const char *base_name;
  int i;

  ndfa_flag = 0;
  split_argument = 0;  /* default value */
  no_minimization_flag = 0;
  time_flag = 0;
  v_flag = 0;
  w_flag = 0;
  progress_flag = 0;
  for (i = 2; i < argc; i++)
    if (strcmp (argv [i], NO_MINIMIZATION_OPTION) == 0)
      no_minimization_flag = 1;
    else if (strcmp (argv [i], TIME_OPTION) == 0)
      time_flag = 1;
    else if (strcmp (argv [i], V_OPTION) == 0)
      v_flag = 1;
    else if (strcmp (argv [i], W_OPTION) == 0)
      w_flag = 1;
    else if (strcmp (argv [i], NDFA_OPTION) == 0)
      ndfa_flag = 1;
    else if (strcmp (argv [i], PROGRESS_OPTION) == 0)
      progress_flag = 1;
    else if (strcmp (argv [i], "-split") == 0)
      {
	if (i + 1 >= argc)
	  fatal ("-split has no argument.");
	fatal ("option `-split' has not been implemented yet\n");
	/* split_argument = atoi (argument_vect [i + 1]); */
      }

  /* Initialize IR storage.  */
  obstack_init (&irp);
  initiate_automaton_decl_table ();
  initiate_insn_decl_table ();
  initiate_decl_table ();
  output_file = stdout;
  output_description_file = NULL;
  base_name = base_file_name (argv[1]);
  obstack_grow (&irp, base_name,
		strlen (base_name) - strlen (file_name_suffix (base_name)));
  obstack_grow (&irp, STANDARD_OUTPUT_DESCRIPTION_FILE_SUFFIX,
		strlen (STANDARD_OUTPUT_DESCRIPTION_FILE_SUFFIX) + 1);
  obstack_1grow (&irp, '\0');
  output_description_file_name = obstack_base (&irp);
  (void) obstack_finish (&irp);
}