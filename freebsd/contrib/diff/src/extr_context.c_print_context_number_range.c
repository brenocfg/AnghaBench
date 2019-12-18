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
 int /*<<< orphan*/  translate_range (struct file_data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,long*) ; 

__attribute__((used)) static void
print_context_number_range (struct file_data const *file, lin a, lin b)
{
  long int trans_a, trans_b;
  translate_range (file, a, b, &trans_a, &trans_b);

  /* We can have B <= A in the case of a range of no lines.
     In this case, we should print the line number before the range,
     which is B.

     POSIX 1003.1-2001 requires two line numbers separated by a comma
     even if the line numbers are the same.  However, this does not
     match existing practice and is surely an error in the
     specification.  */

  if (trans_b <= trans_a)
    fprintf (outfile, "%ld", trans_b);
  else
    fprintf (outfile, "%ld,%ld", trans_a, trans_b);
}