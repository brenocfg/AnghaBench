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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_RT ; 
 scalar_t__ ISTREAM_FILE ; 
 char* _ (char*) ; 
 char* choose_temp_base () ; 
 int /*<<< orphan*/  close_input_stream ; 
 int /*<<< orphan*/ * cpp_pipe ; 
 char* cpp_temp_file ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ istream_type ; 
 int /*<<< orphan*/ * popen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ run_cmd (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  xatexit (int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static FILE *
open_input_stream (char *cmd)
{
  if (istream_type == ISTREAM_FILE)
    {
      char *fileprefix;

      fileprefix = choose_temp_base ();
      cpp_temp_file = (char *) xmalloc (strlen (fileprefix) + 5);
      sprintf (cpp_temp_file, "%s.irc", fileprefix);
      free (fileprefix);

      if (run_cmd (cmd, cpp_temp_file))
	fatal (_("can't execute `%s': %s"), cmd, strerror (errno));

      cpp_pipe = fopen (cpp_temp_file, FOPEN_RT);;
      if (cpp_pipe == NULL)
	fatal (_("can't open temporary file `%s': %s"),
	       cpp_temp_file, strerror (errno));

      if (verbose)
	fprintf (stderr,
	         _("Using temporary file `%s' to read preprocessor output\n"),
		 cpp_temp_file);
    }
  else
    {
      cpp_pipe = popen (cmd, FOPEN_RT);
      if (cpp_pipe == NULL)
	fatal (_("can't popen `%s': %s"), cmd, strerror (errno));
      if (verbose)
	fprintf (stderr, _("Using popen to read preprocessor output\n"));
    }

  xatexit (close_input_stream);
  return cpp_pipe;
}