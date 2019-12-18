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
 int MAX_COLUMNS ; 
 int column ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int quote_string_for_make (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
wrap_output (FILE *f, char *string, int spacer)
{
  int len = quote_string_for_make (NULL, string);

  if (len == 0)
    return;

  if (column
      && (MAX_COLUMNS
	  - 1 /* spacer */
	  - 2 /* ` \'   */
	  < column + len))
    {
      fprintf (f, " \\\n ");
      column = 0;
      if (spacer == ' ')
	spacer = '\0';
    }

  if (spacer == ' ')
    {
      putc (spacer, f);
      ++column;
    }

  quote_string_for_make (f, string);
  column += len;

  if (spacer == ':')
    {
      putc (spacer, f);
      ++column;
    }
}