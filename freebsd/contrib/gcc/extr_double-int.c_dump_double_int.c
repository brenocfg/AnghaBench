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
typedef  int /*<<< orphan*/  double_int ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  double_int_neg (int /*<<< orphan*/ ) ; 
 scalar_t__ double_int_negative_p (int /*<<< orphan*/ ) ; 
 unsigned int double_int_split_digit (int /*<<< orphan*/ *,int) ; 
 scalar_t__ double_int_zero_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
dump_double_int (FILE *file, double_int cst, bool uns)
{
  unsigned digits[100], n;
  int i;

  if (double_int_zero_p (cst))
    {
      fprintf (file, "0");
      return;
    }

  if (!uns && double_int_negative_p (cst))
    {
      fprintf (file, "-");
      cst = double_int_neg (cst);
    }

  for (n = 0; !double_int_zero_p (cst); n++)
    digits[n] = double_int_split_digit (&cst, 10);
  for (i = n - 1; i >= 0; i--)
    fprintf (file, "%u", digits[i]);
}