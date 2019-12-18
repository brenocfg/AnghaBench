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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
show (FILE *stream, const char *string, int *col_p, int *first_p)
{
  if (*first_p)
    {
      fprintf (stream, "%24s", "");
      *col_p = 24;
    }
  else
    {
      fprintf (stream, ", ");
      *col_p += 2;
    }

  if (*col_p + strlen (string) > 72)
    {
      fprintf (stream, "\n%24s", "");
      *col_p = 24;
    }

  fprintf (stream, "%s", string);
  *col_p += strlen (string);

  *first_p = 0;
}