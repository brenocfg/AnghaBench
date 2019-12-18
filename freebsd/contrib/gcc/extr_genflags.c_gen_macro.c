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
 char TOUPPER (char const) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
gen_macro (const char *name, int real, int expect)
{
  int i;

  gcc_assert (real <= expect);
  gcc_assert (real);

  /* #define GEN_CALL(A, B, C, D) gen_call((A), (B)) */
  fputs ("#define GEN_", stdout);
  for (i = 0; name[i]; i++)
    putchar (TOUPPER (name[i]));

  putchar('(');
  for (i = 0; i < expect - 1; i++)
    printf ("%c, ", i + 'A');
  printf ("%c) gen_%s (", i + 'A', name);

  for (i = 0; i < real - 1; i++)
    printf ("(%c), ", i + 'A');
  printf ("(%c))\n", i + 'A');
}