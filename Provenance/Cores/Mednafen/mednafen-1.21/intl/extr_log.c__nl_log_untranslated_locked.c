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
 int /*<<< orphan*/  MSGCTXT_SEPARATOR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * last_logfile ; 
 char* last_logfilename ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  print_escaped (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline void
_nl_log_untranslated_locked (const char *logfilename, const char *domainname,
                             const char *msgid1, const char *msgid2, int plural)
{
  FILE *logfile;
  const char *separator;

  /* Can we reuse the last opened logfile?  */
  if (last_logfilename == NULL || strcmp (logfilename, last_logfilename) != 0)
    {
      /* Close the last used logfile.  */
      if (last_logfilename != NULL)
        {
          if (last_logfile != NULL)
            {
              fclose (last_logfile);
              last_logfile = NULL;
            }
          free (last_logfilename);
          last_logfilename = NULL;
        }
      /* Open the logfile.  */
      last_logfilename = (char *) malloc (strlen (logfilename) + 1);
      if (last_logfilename == NULL)
        return;
      strcpy (last_logfilename, logfilename);
      last_logfile = fopen (logfilename, "a");
      if (last_logfile == NULL)
        return;
    }
  logfile = last_logfile;

  fprintf (logfile, "domain ");
  print_escaped (logfile, domainname, domainname + strlen (domainname));
  separator = strchr (msgid1, MSGCTXT_SEPARATOR);
  if (separator != NULL)
    {
      /* The part before the MSGCTXT_SEPARATOR is the msgctxt.  */
      fprintf (logfile, "\nmsgctxt ");
      print_escaped (logfile, msgid1, separator);
      msgid1 = separator + 1;
    }
  fprintf (logfile, "\nmsgid ");
  print_escaped (logfile, msgid1, msgid1 + strlen (msgid1));
  if (plural)
    {
      fprintf (logfile, "\nmsgid_plural ");
      print_escaped (logfile, msgid2, msgid2 + strlen (msgid2));
      fprintf (logfile, "\nmsgstr[0] \"\"\n");
    }
  else
    fprintf (logfile, "\nmsgstr \"\"\n");
  putc ('\n', logfile);
}