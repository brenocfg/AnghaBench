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
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cmdline_dump_sects ; 
 int /*<<< orphan*/ * dump_sects ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ num_cmdline_dump_sects ; 
 scalar_t__ num_dump_sects ; 
 int optind ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int process_file (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int show_name ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 

int
main (int argc, char **argv)
{
  int err;

#if defined (HAVE_SETLOCALE) && defined (HAVE_LC_MESSAGES)
  setlocale (LC_MESSAGES, "");
#endif
#if defined (HAVE_SETLOCALE)
  setlocale (LC_CTYPE, "");
#endif
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);

  expandargv (&argc, &argv);

  parse_args (argc, argv);

  if (num_dump_sects > 0)
    {
      /* Make a copy of the dump_sects array.  */
      cmdline_dump_sects = malloc (num_dump_sects);
      if (cmdline_dump_sects == NULL)
	error (_("Out of memory allocating dump request table.\n"));
      else
	{
	  memcpy (cmdline_dump_sects, dump_sects, num_dump_sects);
	  num_cmdline_dump_sects = num_dump_sects;
	}
    }

  if (optind < (argc - 1))
    show_name = 1;

  err = 0;
  while (optind < argc)
    err |= process_file (argv[optind++]);

  if (dump_sects != NULL)
    free (dump_sects);
  if (cmdline_dump_sects != NULL)
    free (cmdline_dump_sects);

  return err;
}