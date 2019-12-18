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
 int /*<<< orphan*/  fatal_expected_char (int /*<<< orphan*/ *,char,int) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_rtx_lineno ; 

int
read_skip_spaces (FILE *infile)
{
  int c;

  while (1)
    {
      c = getc (infile);
      switch (c)
	{
	case '\n':
	  read_rtx_lineno++;
	  break;

	case ' ': case '\t': case '\f': case '\r':
	  break;

	case ';':
	  do
	    c = getc (infile);
	  while (c != '\n' && c != EOF);
	  read_rtx_lineno++;
	  break;

	case '/':
	  {
	    int prevc;
	    c = getc (infile);
	    if (c != '*')
	      fatal_expected_char (infile, '*', c);

	    prevc = 0;
	    while ((c = getc (infile)) && c != EOF)
	      {
		if (c == '\n')
		   read_rtx_lineno++;
	        else if (prevc == '*' && c == '/')
		  break;
	        prevc = c;
	      }
	  }
	  break;

	default:
	  return c;
	}
    }
}