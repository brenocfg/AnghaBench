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
typedef  scalar_t__* lambda_vector ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
print_linear_expression (FILE * outfile, lambda_vector expr, int size,
			 char start)
{
  int i;
  bool first = true;
  for (i = 0; i < size; i++)
    {
      if (expr[i] != 0)
	{
	  if (first)
	    {
	      if (expr[i] < 0)
		fprintf (outfile, "-");
	      first = false;
	    }
	  else if (expr[i] > 0)
	    fprintf (outfile, " + ");
	  else
	    fprintf (outfile, " - ");
	  if (abs (expr[i]) == 1)
	    fprintf (outfile, "%c", start + i);
	  else
	    fprintf (outfile, "%d%c", abs (expr[i]), start + i);
	}
    }
}