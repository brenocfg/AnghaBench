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
struct ui_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ PRINT_LITERAL_FORM (int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,unsigned int) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 

__attribute__((used)) static void
pascal_one_char (int c, struct ui_file *stream, int *in_quotes)
{

  c &= 0xFF;			/* Avoid sign bit follies */

  if ((c == '\'') || (PRINT_LITERAL_FORM (c)))
    {
      if (!(*in_quotes))
	fputs_filtered ("'", stream);
      *in_quotes = 1;
      if (c == '\'')
	{
	  fputs_filtered ("''", stream);
	}
      else
	fprintf_filtered (stream, "%c", c);
    }
  else
    {
      if (*in_quotes)
	fputs_filtered ("'", stream);
      *in_quotes = 0;
      fprintf_filtered (stream, "#%d", (unsigned int) c);
    }
}