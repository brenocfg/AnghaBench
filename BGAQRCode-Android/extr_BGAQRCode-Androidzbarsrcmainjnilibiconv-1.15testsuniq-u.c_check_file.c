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
struct linebuffer {char* buffer; size_t length; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  different (char*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  freebuffer (struct linebuffer*) ; 
 int /*<<< orphan*/  initbuffer (struct linebuffer*) ; 
 char* program_name ; 
 scalar_t__ readline (struct linebuffer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  writeline (struct linebuffer*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
check_file (const char *infile, const char *outfile)
{
  FILE *istream;
  FILE *ostream;
  struct linebuffer lb1, lb2;
  struct linebuffer *thisline, *prevline, *exch;
  char *prevfield, *thisfield;
  size_t prevlen, thislen;
  int match_count = 0;

  if (!strcmp (infile, "-"))
    istream = stdin;
  else
    istream = fopen (infile, "r");
  if (istream == NULL)
    {
      fprintf (stderr, "%s: error opening %s\n", program_name, infile);
      exit (1);
    }

  if (!strcmp (outfile, "-"))
    ostream = stdout;
  else
    ostream = fopen (outfile, "w");
  if (ostream == NULL)
    {
      fprintf (stderr, "%s: error opening %s\n", program_name, outfile);
      exit (1);
    }

  thisline = &lb1;
  prevline = &lb2;

  initbuffer (thisline);
  initbuffer (prevline);

  if (readline (prevline, istream) == 0)
    goto closefiles;
  prevfield = prevline->buffer;
  prevlen = prevline->length;

  while (!feof (istream))
    {
      int match;
      if (readline (thisline, istream) == 0)
        break;
      thisfield = thisline->buffer;
      thislen = thisline->length;
      match = !different (thisfield, prevfield, thislen, prevlen);

      if (match)
        ++match_count;

      if (!match)
        {
          writeline (prevline, ostream, match_count);
          exch = prevline;
          prevline = thisline;
          thisline = exch;
          prevfield = thisfield;
          prevlen = thislen;
          if (!match)
            match_count = 0;
        }
    }

  writeline (prevline, ostream, match_count);

 closefiles:
  if (ferror (istream) || fclose (istream) == EOF)
    {
      fprintf (stderr, "%s: error reading %s\n", program_name, infile);
      exit (1);
    }

  if (ferror (ostream) || fclose (ostream) == EOF)
    {
      fprintf (stderr, "%s: error writing %s\n", program_name, outfile);
      exit (1);
    }

  freebuffer (&lb1);
  freebuffer (&lb2);
}