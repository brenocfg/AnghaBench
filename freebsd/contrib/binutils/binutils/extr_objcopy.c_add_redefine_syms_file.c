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
 int EOF ; 
 scalar_t__ IS_LINE_TERMINATOR (int) ; 
 scalar_t__ IS_WHITESPACE (int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redefine_list_append (char const*,char*,char*) ; 
 int strerror (int /*<<< orphan*/ ) ; 
 char* xmalloc (size_t) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
add_redefine_syms_file (const char *filename)
{
  FILE *file;
  char *buf;
  size_t bufsize;
  size_t len;
  size_t outsym_off;
  int c, lineno;

  file = fopen (filename, "r");
  if (file == NULL)
    fatal (_("couldn't open symbol redefinition file %s (error: %s)"),
	   filename, strerror (errno));

  bufsize = 100;
  buf = xmalloc (bufsize);

  lineno = 1;
  c = getc (file);
  len = 0;
  outsym_off = 0;
  while (c != EOF)
    {
      /* Collect the input symbol name.  */
      while (! IS_WHITESPACE (c) && ! IS_LINE_TERMINATOR (c) && c != EOF)
	{
	  if (c == '#')
	    goto comment;
	  buf[len++] = c;
	  if (len >= bufsize)
	    {
	      bufsize *= 2;
	      buf = xrealloc (buf, bufsize);
	    }
	  c = getc (file);
	}
      buf[len++] = '\0';
      if (c == EOF)
	break;

      /* Eat white space between the symbol names.  */
      while (IS_WHITESPACE (c))
	c = getc (file);
      if (c == '#' || IS_LINE_TERMINATOR (c))
	goto comment;
      if (c == EOF)
	break;

      /* Collect the output symbol name.  */
      outsym_off = len;
      while (! IS_WHITESPACE (c) && ! IS_LINE_TERMINATOR (c) && c != EOF)
	{
	  if (c == '#')
	    goto comment;
	  buf[len++] = c;
	  if (len >= bufsize)
	    {
	      bufsize *= 2;
	      buf = xrealloc (buf, bufsize);
	    }
	  c = getc (file);
	}
      buf[len++] = '\0';
      if (c == EOF)
	break;

      /* Eat white space at end of line.  */
      while (! IS_LINE_TERMINATOR(c) && c != EOF && IS_WHITESPACE (c))
	c = getc (file);
      if (c == '#')
	goto comment;
      /* Handle \r\n.  */
      if ((c == '\r' && (c = getc (file)) == '\n')
	  || c == '\n' || c == EOF)
	{
 end_of_line:
	  /* Append the redefinition to the list.  */
	  if (buf[0] != '\0')
	    redefine_list_append (filename, &buf[0], &buf[outsym_off]);

	  lineno++;
	  len = 0;
	  outsym_off = 0;
	  if (c == EOF)
	    break;
	  c = getc (file);
	  continue;
	}
      else
	fatal (_("%s:%d: garbage found at end of line"), filename, lineno);
 comment:
      if (len != 0 && (outsym_off == 0 || outsym_off == len))
	fatal (_("%s:%d: missing new symbol name"), filename, lineno);
      buf[len++] = '\0';

      /* Eat the rest of the line and finish it.  */
      while (c != '\n' && c != EOF)
	c = getc (file);
      goto end_of_line;
    }

  if (len != 0)
    fatal (_("%s:%d: premature end of file"), filename, lineno);

  free (buf);
}