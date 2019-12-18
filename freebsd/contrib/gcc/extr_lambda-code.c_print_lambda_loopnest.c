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
typedef  int /*<<< orphan*/  lambda_loopnest ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LN_DEPTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LN_INVARIANTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LN_LOOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_lambda_loop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char) ; 

void
print_lambda_loopnest (FILE * outfile, lambda_loopnest nest, char start)
{
  int i;
  for (i = 0; i < LN_DEPTH (nest); i++)
    {
      fprintf (outfile, "Loop %c\n", start + i);
      print_lambda_loop (outfile, LN_LOOPS (nest)[i], LN_DEPTH (nest),
			 LN_INVARIANTS (nest), 'i');
      fprintf (outfile, "\n");
    }
}