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

/* Variables and functions */
 char* accessor_from_format (char const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 char* type_from_format (char const) ; 

__attribute__((used)) static void
gendef (const char *format)
{
  const char *p;
  int i, j;

  /* Start by writing the definition of the function name and the types
     of the arguments.  */

  printf ("rtx\ngen_rtx_fmt_%s (RTX_CODE code, enum machine_mode mode", format);
  for (p = format, i = 0; *p != 0; p++)
    if (*p != '0')
      printf (",\n\t%sarg%d", type_from_format (*p), i++);

  puts (")");

  /* Now write out the body of the function itself, which allocates
     the memory and initializes it.  */
  puts ("{");
  puts ("  rtx rt;");
  puts ("  rt = rtx_alloc (code);\n");

  puts ("  PUT_MODE (rt, mode);");

  for (p = format, i = j = 0; *p ; ++p, ++i)
    if (*p != '0')
      printf ("  %s (rt, %d) = arg%d;\n", accessor_from_format (*p), i, j++);
    else
      printf ("  X0EXP (rt, %d) = NULL_RTX;\n", i);

  puts ("\n  return rt;\n}\n");
}