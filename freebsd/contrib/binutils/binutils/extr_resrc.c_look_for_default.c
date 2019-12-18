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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* DEFAULT_PREPROCESSOR ; 
 int /*<<< orphan*/  EXECUTABLE_SUFFIX ; 
 char* _ (char*) ; 
 int /*<<< orphan*/ * cpp_pipe ; 
 scalar_t__ filename_need_quotes (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * open_input_stream (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strcat (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static FILE *
look_for_default (char *cmd, const char *prefix, int end_prefix,
		  const char *preprocargs, const char *filename)
{
  char *space;
  int found;
  struct stat s;
  const char *fnquotes = (filename_need_quotes (filename) ? "\"" : "");

  strcpy (cmd, prefix);

  sprintf (cmd + end_prefix, "%s", DEFAULT_PREPROCESSOR);
  space = strchr (cmd + end_prefix, ' ');
  if (space)
    *space = 0;

  if (
#if defined (__DJGPP__) || defined (__CYGWIN__) || defined (_WIN32)
      strchr (cmd, '\\') ||
#endif
      strchr (cmd, '/'))
    {
      found = (stat (cmd, &s) == 0
#ifdef HAVE_EXECUTABLE_SUFFIX
	       || stat (strcat (cmd, EXECUTABLE_SUFFIX), &s) == 0
#endif
	       );

      if (! found)
	{
	  if (verbose)
	    fprintf (stderr, _("Tried `%s'\n"), cmd);
	  return NULL;
	}
    }

  strcpy (cmd, prefix);

  sprintf (cmd + end_prefix, "%s %s %s%s%s",
	   DEFAULT_PREPROCESSOR, preprocargs, fnquotes, filename, fnquotes);

  if (verbose)
    fprintf (stderr, _("Using `%s'\n"), cmd);

  cpp_pipe = open_input_stream (cmd);
  return cpp_pipe;
}