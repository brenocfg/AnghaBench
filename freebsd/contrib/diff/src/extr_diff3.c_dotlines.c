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
struct diff3_block {int dummy; } ;
typedef  scalar_t__ lin ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ D_NUMLINES (struct diff3_block*,int) ; 
 int /*<<< orphan*/  D_RELLEN (struct diff3_block*,int,scalar_t__) ; 
 char* D_RELNUM (struct diff3_block*,int,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
dotlines (FILE *outputfile, struct diff3_block *b, int filenum)
{
  lin i;
  bool leading_dot = false;

  for (i = 0;
       i < D_NUMLINES (b, filenum);
       i++)
    {
      char *line = D_RELNUM (b, filenum, i);
      if (line[0] == '.')
	{
	  leading_dot = true;
	  fprintf (outputfile, ".");
	}
      fwrite (line, sizeof (char),
	      D_RELLEN (b, filenum, i), outputfile);
    }

  return leading_dot;
}