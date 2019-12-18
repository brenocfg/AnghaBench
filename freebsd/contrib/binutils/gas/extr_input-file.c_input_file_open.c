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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_RT ; 
 scalar_t__ ISSPACE (char) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  as_bad (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * f_in ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* file_name ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int preprocess ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xstrerror (int /*<<< orphan*/ ) ; 

void
input_file_open (char *filename, /* "" means use stdin. Must not be 0.  */
		 int pre)
{
  int c;
  char buf[80];

  preprocess = pre;

  assert (filename != 0);	/* Filename may not be NULL.  */
  if (filename[0])
    {
      f_in = fopen (filename, FOPEN_RT);
      file_name = filename;
    }
  else
    {
      /* Use stdin for the input file.  */
      f_in = stdin;
      /* For error messages.  */
      file_name = _("{standard input}");
    }

  if (f_in == NULL)
    {
      as_bad (_("can't open %s for reading: %s"),
	      file_name, xstrerror (errno));
      return;
    }

  c = getc (f_in);

  if (ferror (f_in))
    {
      as_bad (_("can't read from %s: %s"),
	      file_name, xstrerror (errno));

      fclose (f_in);
      f_in = NULL;
      return;
    }

  if (c == '#')
    {
      /* Begins with comment, may not want to preprocess.  */
      c = getc (f_in);
      if (c == 'N')
	{
	  if (fgets (buf, sizeof (buf), f_in)
	      && !strncmp (buf, "O_APP", 5) && ISSPACE (buf[5]))
	    preprocess = 0;
	  if (!strchr (buf, '\n'))
	    ungetc ('#', f_in);	/* It was longer.  */
	  else
	    ungetc ('\n', f_in);
	}
      else if (c == 'A')
	{
	  if (fgets (buf, sizeof (buf), f_in)
	      && !strncmp (buf, "PP", 2) && ISSPACE (buf[2]))
	    preprocess = 1;
	  if (!strchr (buf, '\n'))
	    ungetc ('#', f_in);
	  else
	    ungetc ('\n', f_in);
	}
      else if (c == '\n')
	ungetc ('\n', f_in);
      else
	ungetc ('#', f_in);
    }
  else
    ungetc (c, f_in);
}