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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
output_range_type (FILE *f, long int min_range_value,
		   long int max_range_value)
{
  if (min_range_value >= 0 && max_range_value <= 255)
    fprintf (f, "unsigned char");
  else if (min_range_value >= -127 && max_range_value <= 127)
    fprintf (f, "signed char");
  else if (min_range_value >= 0 && max_range_value <= 65535)
    fprintf (f, "unsigned short");
  else if (min_range_value >= -32767 && max_range_value <= 32767)
    fprintf (f, "short");
  else
    fprintf (f, "int");
}