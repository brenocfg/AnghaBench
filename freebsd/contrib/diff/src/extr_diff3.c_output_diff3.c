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
struct diff3_block {int correspond; } ;
typedef  int lin ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DIFF_1ST 131 
#define  DIFF_2ND 130 
#define  DIFF_3RD 129 
#define  DIFF_ALL 128 
 int D_HIGHLINE (struct diff3_block*,int) ; 
 int D_LOWLINE (struct diff3_block*,int) ; 
 struct diff3_block* D_NEXT (struct diff3_block*) ; 
 size_t D_RELLEN (struct diff3_block*,int,int) ; 
 char* D_RELNUM (struct diff3_block*,int,int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char const*,...) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ initial_tab ; 

__attribute__((used)) static void
output_diff3 (FILE *outputfile, struct diff3_block *diff,
	      int const mapping[3], int const rev_mapping[3])
{
  int i;
  int oddoneout;
  char *cp;
  struct diff3_block *ptr;
  lin line;
  size_t length;
  int dontprint;
  static int skew_increment[3] = { 2, 3, 1 }; /* 0==>2==>1==>3 */
  char const *line_prefix = initial_tab ? "\t" : "  ";

  for (ptr = diff; ptr; ptr = D_NEXT (ptr))
    {
      char x[2];

      switch (ptr->correspond)
	{
	case DIFF_ALL:
	  x[0] = 0;
	  dontprint = 3;	/* Print them all */
	  oddoneout = 3;	/* Nobody's odder than anyone else */
	  break;
	case DIFF_1ST:
	case DIFF_2ND:
	case DIFF_3RD:
	  oddoneout = rev_mapping[ptr->correspond - DIFF_1ST];

	  x[0] = oddoneout + '1';
	  x[1] = 0;
	  dontprint = oddoneout == 0;
	  break;
	default:
	  fatal ("internal error: invalid diff type passed to output");
	}
      fprintf (outputfile, "====%s\n", x);

      /* Go 0, 2, 1 if the first and third outputs are equivalent.  */
      for (i = 0; i < 3;
	   i = (oddoneout == 1 ? skew_increment[i] : i + 1))
	{
	  int realfile = mapping[i];
	  lin lowt = D_LOWLINE (ptr, realfile);
	  lin hight = D_HIGHLINE (ptr, realfile);
	  long int llowt = lowt;
	  long int lhight = hight;

	  fprintf (outputfile, "%d:", i + 1);
	  switch (lowt - hight)
	    {
	    case 1:
	      fprintf (outputfile, "%lda\n", llowt - 1);
	      break;
	    case 0:
	      fprintf (outputfile, "%ldc\n", llowt);
	      break;
	    default:
	      fprintf (outputfile, "%ld,%ldc\n", llowt, lhight);
	      break;
	    }

	  if (i == dontprint) continue;

	  if (lowt <= hight)
	    {
	      line = 0;
	      do
		{
		  fprintf (outputfile, line_prefix);
		  cp = D_RELNUM (ptr, realfile, line);
		  length = D_RELLEN (ptr, realfile, line);
		  fwrite (cp, sizeof (char), length, outputfile);
		}
	      while (++line < hight - lowt + 1);
	      if (cp[length - 1] != '\n')
		fprintf (outputfile, "\n\\ %s\n",
			 _("No newline at end of file"));
	    }
	}
    }
}