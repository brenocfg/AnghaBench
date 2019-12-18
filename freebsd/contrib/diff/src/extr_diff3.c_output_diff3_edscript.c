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
typedef  enum diff_type { ____Placeholder_diff_type } diff_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t DIFF_1ST ; 
#define  DIFF_2ND 130 
#define  DIFF_3RD 129 
#define  DIFF_ALL 128 
 long D_HIGHLINE (struct diff3_block*,int const) ; 
 long D_LOWLINE (struct diff3_block*,int const) ; 
 scalar_t__ D_NUMLINES (struct diff3_block*,int const) ; 
 size_t FILE0 ; 
 size_t FILE1 ; 
 size_t FILE2 ; 
 int dotlines (int /*<<< orphan*/ *,struct diff3_block*,int const) ; 
 scalar_t__ finalwrite ; 
 int flagging ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  overlap_only ; 
 struct diff3_block* reverse_diff3_blocklist (struct diff3_block*) ; 
 scalar_t__ show_2nd ; 
 int /*<<< orphan*/  simple_only ; 
 int /*<<< orphan*/  undotlines (int /*<<< orphan*/ *,int,long,scalar_t__) ; 

__attribute__((used)) static bool
output_diff3_edscript (FILE *outputfile, struct diff3_block *diff,
		       int const mapping[3], int const rev_mapping[3],
		       char const *file0, char const *file1, char const *file2)
{
  bool leading_dot;
  bool conflicts_found = false;
  bool conflict;
  struct diff3_block *b;

  for (b = reverse_diff3_blocklist (diff); b; b = b->next)
    {
      /* Must do mapping correctly.  */
      enum diff_type type
	= (b->correspond == DIFF_ALL
	   ? DIFF_ALL
	   : DIFF_1ST + rev_mapping[b->correspond - DIFF_1ST]);

      long int low0, high0;

      /* If we aren't supposed to do this output block, skip it.  */
      switch (type)
	{
	default: continue;
	case DIFF_2ND: if (!show_2nd) continue; conflict = true; break;
	case DIFF_3RD: if (overlap_only) continue; conflict = false; break;
	case DIFF_ALL: if (simple_only) continue; conflict = flagging; break;
	}

      low0 = D_LOWLINE (b, mapping[FILE0]);
      high0 = D_HIGHLINE (b, mapping[FILE0]);

      if (conflict)
	{
	  conflicts_found = true;


	  /* Mark end of conflict.  */

	  fprintf (outputfile, "%lda\n", high0);
	  leading_dot = false;
	  if (type == DIFF_ALL)
	    {
	      if (show_2nd)
		{
		  /* Append lines from FILE1.  */
		  fprintf (outputfile, "||||||| %s\n", file1);
		  leading_dot = dotlines (outputfile, b, mapping[FILE1]);
		}
	      /* Append lines from FILE2.  */
	      fprintf (outputfile, "=======\n");
	      leading_dot |= dotlines (outputfile, b, mapping[FILE2]);
	    }
	  fprintf (outputfile, ">>>>>>> %s\n", file2);
	  undotlines (outputfile, leading_dot, high0 + 2,
		      (D_NUMLINES (b, mapping[FILE1])
		       + D_NUMLINES (b, mapping[FILE2]) + 1));


	  /* Mark start of conflict.  */

	  fprintf (outputfile, "%lda\n<<<<<<< %s\n", low0 - 1,
		   type == DIFF_ALL ? file0 : file1);
	  leading_dot = false;
	  if (type == DIFF_2ND)
	    {
	      /* Prepend lines from FILE1.  */
	      leading_dot = dotlines (outputfile, b, mapping[FILE1]);
	      fprintf (outputfile, "=======\n");
	    }
	  undotlines (outputfile, leading_dot, low0 + 1,
		      D_NUMLINES (b, mapping[FILE1]));
	}
      else if (D_NUMLINES (b, mapping[FILE2]) == 0)
	/* Write out a delete */
	{
	  if (low0 == high0)
	    fprintf (outputfile, "%ldd\n", low0);
	  else
	    fprintf (outputfile, "%ld,%ldd\n", low0, high0);
	}
      else
	/* Write out an add or change */
	{
	  switch (high0 - low0)
	    {
	    case -1:
	      fprintf (outputfile, "%lda\n", high0);
	      break;
	    case 0:
	      fprintf (outputfile, "%ldc\n", high0);
	      break;
	    default:
	      fprintf (outputfile, "%ld,%ldc\n", low0, high0);
	      break;
	    }

	  undotlines (outputfile, dotlines (outputfile, b, mapping[FILE2]),
		      low0, D_NUMLINES (b, mapping[FILE2]));
	}
    }
  if (finalwrite) fprintf (outputfile, "w\nq\n");
  return conflicts_found;
}