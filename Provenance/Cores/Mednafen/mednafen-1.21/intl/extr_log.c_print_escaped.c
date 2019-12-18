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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_escaped (FILE *stream, const char *str, const char *str_end)
{
  putc ('"', stream);
  for (; str != str_end; str++)
    if (*str == '\n')
      {
        fputs ("\\n\"", stream);
        if (str + 1 == str_end)
          return;
        fputs ("\n\"", stream);
      }
    else
      {
        if (*str == '"' || *str == '\\')
          putc ('\\', stream);
        putc (*str, stream);
      }
  putc ('"', stream);
}