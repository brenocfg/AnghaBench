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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char*,int) ; 
 char* read_rtx_filename ; 
 int read_rtx_lineno ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  string_obstack ; 

__attribute__((used)) static void
read_escape (FILE *infile)
{
  int c = getc (infile);

  switch (c)
    {
      /* Backslash-newline is replaced by nothing, as in C.  */
    case '\n':
      read_rtx_lineno++;
      return;

      /* \" \' \\ are replaced by the second character.  */
    case '\\':
    case '"':
    case '\'':
      break;

      /* Standard C string escapes:
	 \a \b \f \n \r \t \v
	 \[0-7] \x
	 all are passed through to the output string unmolested.
	 In normal use these wind up in a string constant processed
	 by the C compiler, which will translate them appropriately.
	 We do not bother checking that \[0-7] are followed by up to
	 two octal digits, or that \x is followed by N hex digits.
	 \? \u \U are left out because they are not in traditional C.  */
    case 'a': case 'b': case 'f': case 'n': case 'r': case 't': case 'v':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6':
    case '7': case 'x':
      obstack_1grow (&string_obstack, '\\');
      break;

      /* \; makes stuff for a C string constant containing
	 newline and tab.  */
    case ';':
      obstack_grow (&string_obstack, "\\n\\t", 4);
      return;

      /* pass anything else through, but issue a warning.  */
    default:
      fprintf (stderr, "%s:%d: warning: unrecognized escape \\%c\n",
	       read_rtx_filename, read_rtx_lineno, c);
      obstack_1grow (&string_obstack, '\\');
      break;
    }

  obstack_1grow (&string_obstack, c);
}