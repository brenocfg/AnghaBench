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
 scalar_t__ ISPRINT (char) ; 
 int /*<<< orphan*/  OUTPUT_QUOTED_STRING (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

void
output_quoted_string (FILE *asm_file, const char *string)
{
#ifdef OUTPUT_QUOTED_STRING
  OUTPUT_QUOTED_STRING (asm_file, string);
#else
  char c;

  putc ('\"', asm_file);
  while ((c = *string++) != 0)
    {
      if (ISPRINT (c))
	{
	  if (c == '\"' || c == '\\')
	    putc ('\\', asm_file);
	  putc (c, asm_file);
	}
      else
	fprintf (asm_file, "\\%03o", (unsigned char) c);
    }
  putc ('\"', asm_file);
#endif
}