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
 int arm_get_strip_length (char const) ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 

void
arm_asm_output_labelref (FILE *stream, const char *name)
{
  int skip;
  int verbatim = 0;

  while ((skip = arm_get_strip_length (* name)))
    {
      verbatim |= (*name == '*');
      name += skip;
    }

  if (verbatim)
    fputs (name, stream);
  else
    asm_fprintf (stream, "%U%s", name);
}