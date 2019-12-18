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
struct file_data {int dummy; } ;
typedef  int /*<<< orphan*/  lin ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long,...) ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  translate_range (struct file_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,long*) ; 

void
print_number_range (char sepchar, struct file_data *file, lin a, lin b)
{
  long int trans_a, trans_b;
  translate_range (file, a, b, &trans_a, &trans_b);

  /* Note: we can have B < A in the case of a range of no lines.
     In this case, we should print the line number before the range,
     which is B.  */
  if (trans_b > trans_a)
    fprintf (outfile, "%ld%c%ld", trans_a, sepchar, trans_b);
  else
    fprintf (outfile, "%ld", trans_b);
}