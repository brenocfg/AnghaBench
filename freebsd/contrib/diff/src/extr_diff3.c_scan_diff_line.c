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
 scalar_t__ edscript ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static char *
scan_diff_line (char *scan_ptr, char **set_start, size_t *set_length,
		char *limit, char leadingchar)
{
  char *line_ptr;

  if (!(scan_ptr[0] == leadingchar
	&& scan_ptr[1] == ' '))
    fatal ("invalid diff format; incorrect leading line chars");

  *set_start = line_ptr = scan_ptr + 2;
  while (*line_ptr++ != '\n')
    continue;

  /* Include newline if the original line ended in a newline,
     or if an edit script is being generated.
     Copy any missing newline message to stderr if an edit script is being
     generated, because edit scripts cannot handle missing newlines.
     Return the beginning of the next line.  */
  *set_length = line_ptr - *set_start;
  if (line_ptr < limit && *line_ptr == '\\')
    {
      if (edscript)
	fprintf (stderr, "%s:", program_name);
      else
	--*set_length;
      line_ptr++;
      do
	{
	  if (edscript)
	    putc (*line_ptr, stderr);
	}
      while (*line_ptr++ != '\n');
    }

  return line_ptr;
}