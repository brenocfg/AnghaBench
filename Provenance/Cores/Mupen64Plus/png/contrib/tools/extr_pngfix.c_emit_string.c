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
 char const UCHAR_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const) ; 
 scalar_t__ isgraph (char const) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  putc (char const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
emit_string(const char *str, FILE *out)
   /* Print a string with spaces replaced by '_' and non-printing characters by
    * an octal escape.
    */
{
   for (; *str; ++str)
      if (isgraph(UCHAR_MAX & *str))
         putc(*str, out);

      else if (isspace(UCHAR_MAX & *str))
         putc('_', out);

      else
         fprintf(out, "\\%.3o", *str);
}