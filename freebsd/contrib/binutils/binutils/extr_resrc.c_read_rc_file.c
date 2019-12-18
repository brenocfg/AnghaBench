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
typedef  int /*<<< orphan*/  rc_res_directory ;

/* Variables and functions */
 char* DEFAULT_PREPROCESSOR ; 
 char const* EXECUTABLE_SUFFIX ; 
 int /*<<< orphan*/  ISTREAM_FILE ; 
 int /*<<< orphan*/  ISTREAM_PIPE ; 
 int /*<<< orphan*/  close_input_stream () ; 
 scalar_t__ cpp_pipe ; 
 int /*<<< orphan*/  define_fontdirs () ; 
 scalar_t__ filename_need_quotes (char const*) ; 
 int /*<<< orphan*/ * fontdirs ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  istream_type ; 
 scalar_t__ look_for_default (char*,char*,int,char const*,char const*) ; 
 scalar_t__ open_input_stream (char*) ; 
 char* program_name ; 
 char* rc_filename ; 
 int rc_lineno ; 
 int /*<<< orphan*/  rcparse_discard_strings () ; 
 int /*<<< orphan*/  rcparse_set_language (int) ; 
 int /*<<< orphan*/ * resources ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,char const*,char const*,char const*) ; 
 int strlen (char const*) ; 
 char* xmalloc (int) ; 
 char* xstrdup (char const*) ; 
 int /*<<< orphan*/  yyparse () ; 

rc_res_directory *
read_rc_file (const char *filename, const char *preprocessor,
	      const char *preprocargs, int language, int use_temp_file)
{
  char *cmd;
  const char *fnquotes = (filename_need_quotes (filename) ? "\"" : "");

  istream_type = (use_temp_file) ? ISTREAM_FILE : ISTREAM_PIPE;

  if (preprocargs == NULL)
    preprocargs = "";
  if (filename == NULL)
    filename = "-";

  if (preprocessor)
    {
      cmd = xmalloc (strlen (preprocessor)
		     + strlen (preprocargs)
		     + strlen (filename)
		     + strlen (fnquotes) * 2
		     + 10);
      sprintf (cmd, "%s %s %s%s%s", preprocessor, preprocargs,
	       fnquotes, filename, fnquotes);

      cpp_pipe = open_input_stream (cmd);
    }
  else
    {
      char *dash, *slash, *cp;

      preprocessor = DEFAULT_PREPROCESSOR;

      cmd = xmalloc (strlen (program_name)
		     + strlen (preprocessor)
		     + strlen (preprocargs)
		     + strlen (filename)
		     + strlen (fnquotes) * 2
#ifdef HAVE_EXECUTABLE_SUFFIX
		     + strlen (EXECUTABLE_SUFFIX)
#endif
		     + 10);


      dash = slash = 0;
      for (cp = program_name; *cp; cp++)
	{
	  if (*cp == '-')
	    dash = cp;
	  if (
#if defined (__DJGPP__) || defined (__CYGWIN__) || defined(_WIN32)
	      *cp == ':' || *cp == '\\' ||
#endif
	      *cp == '/')
	    {
	      slash = cp;
	      dash = 0;
	    }
	}

      cpp_pipe = 0;

      if (dash)
	{
	  /* First, try looking for a prefixed gcc in the windres
	     directory, with the same prefix as windres */

	  cpp_pipe = look_for_default (cmd, program_name, dash - program_name + 1,
				       preprocargs, filename);
	}

      if (slash && ! cpp_pipe)
	{
	  /* Next, try looking for a gcc in the same directory as
             that windres */

	  cpp_pipe = look_for_default (cmd, program_name, slash - program_name + 1,
				       preprocargs, filename);
	}

      if (! cpp_pipe)
	{
	  /* Sigh, try the default */

	  cpp_pipe = look_for_default (cmd, "", 0, preprocargs, filename);
	}

    }

  free (cmd);

  rc_filename = xstrdup (filename);
  rc_lineno = 1;
  if (language != -1)
    rcparse_set_language (language);
  yyparse ();
  rcparse_discard_strings ();

  close_input_stream ();

  if (fontdirs != NULL)
    define_fontdirs ();

  free (rc_filename);
  rc_filename = NULL;

  return resources;
}