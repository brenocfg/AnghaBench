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
struct diff3_block {size_t correspond; struct diff3_block* next; } ;
typedef  scalar_t__ lin ;
typedef  enum diff_type { ____Placeholder_diff_type } diff_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t DIFF_1ST ; 
#define  DIFF_2ND 130 
#define  DIFF_3RD 129 
#define  DIFF_ALL 128 
 scalar_t__ D_LOWLINE (struct diff3_block*,size_t) ; 
 scalar_t__ D_NUMLINES (struct diff3_block*,int const) ; 
 int /*<<< orphan*/  D_RELLEN (struct diff3_block*,int const,scalar_t__) ; 
 int /*<<< orphan*/  D_RELNUM (struct diff3_block*,int const,scalar_t__) ; 
 int EOF ; 
 size_t FILE0 ; 
 size_t FILE1 ; 
 size_t FILE2 ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int feof (int /*<<< orphan*/ *) ; 
 int ferror (int /*<<< orphan*/ *) ; 
 int flagging ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,...) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  overlap_only ; 
 int /*<<< orphan*/  perror_with_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 scalar_t__ show_2nd ; 
 int /*<<< orphan*/  simple_only ; 

__attribute__((used)) static bool
output_diff3_merge (FILE *infile, FILE *outputfile, struct diff3_block *diff,
		    int const mapping[3], int const rev_mapping[3],
		    char const *file0, char const *file1, char const *file2)
{
  int c;
  lin i;
  bool conflicts_found = false;
  bool conflict;
  struct diff3_block *b;
  lin linesread = 0;

  for (b = diff; b; b = b->next)
    {
      /* Must do mapping correctly.  */
      enum diff_type type
	= ((b->correspond == DIFF_ALL)
	   ? DIFF_ALL
	   : DIFF_1ST + rev_mapping[b->correspond - DIFF_1ST]);
      char const *format_2nd = "<<<<<<< %s\n";

      /* If we aren't supposed to do this output block, skip it.  */
      switch (type)
	{
	default: continue;
	case DIFF_2ND: if (!show_2nd) continue; conflict = true; break;
	case DIFF_3RD: if (overlap_only) continue; conflict = false; break;
	case DIFF_ALL: if (simple_only) continue; conflict = flagging;
	  format_2nd = "||||||| %s\n";
	  break;
	}

      /* Copy I lines from file 0.  */
      i = D_LOWLINE (b, FILE0) - linesread - 1;
      linesread += i;
      while (0 <= --i)
	do
	  {
	    c = getc (infile);
	    if (c == EOF)
	      {
		if (ferror (infile))
		  perror_with_exit (_("read failed"));
		else if (feof (infile))
		  fatal ("input file shrank");
	      }
	    putc (c, outputfile);
	  }
	while (c != '\n');

      if (conflict)
	{
	  conflicts_found = true;

	  if (type == DIFF_ALL)
	    {
	      /* Put in lines from FILE0 with bracket.  */
	      fprintf (outputfile, "<<<<<<< %s\n", file0);
	      for (i = 0;
		   i < D_NUMLINES (b, mapping[FILE0]);
		   i++)
		fwrite (D_RELNUM (b, mapping[FILE0], i), sizeof (char),
			D_RELLEN (b, mapping[FILE0], i), outputfile);
	    }

	  if (show_2nd)
	    {
	      /* Put in lines from FILE1 with bracket.  */
	      fprintf (outputfile, format_2nd, file1);
	      for (i = 0;
		   i < D_NUMLINES (b, mapping[FILE1]);
		   i++)
		fwrite (D_RELNUM (b, mapping[FILE1], i), sizeof (char),
			D_RELLEN (b, mapping[FILE1], i), outputfile);
	    }

	  fprintf (outputfile, "=======\n");
	}

      /* Put in lines from FILE2.  */
      for (i = 0;
	   i < D_NUMLINES (b, mapping[FILE2]);
	   i++)
	fwrite (D_RELNUM (b, mapping[FILE2], i), sizeof (char),
		D_RELLEN (b, mapping[FILE2], i), outputfile);

      if (conflict)
	fprintf (outputfile, ">>>>>>> %s\n", file2);

      /* Skip I lines in file 0.  */
      i = D_NUMLINES (b, FILE0);
      linesread += i;
      while (0 <= --i)
	while ((c = getc (infile)) != '\n')
	  if (c == EOF)
	    {
	      if (ferror (infile))
		perror_with_exit (_("read failed"));
	      else if (feof (infile))
		{
		  if (i || b->next)
		    fatal ("input file shrank");
		  return conflicts_found;
		}
	    }
    }
  /* Copy rest of common file.  */
  while ((c = getc (infile)) != EOF || !(ferror (infile) | feof (infile)))
    putc (c, outputfile);
  return conflicts_found;
}