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
struct operand_data {char* predicate; char* constraint; int strict_low; int eliminable; int /*<<< orphan*/  mode; struct operand_data* next; } ;

/* Variables and functions */
 char* GET_MODE_NAME (int /*<<< orphan*/ ) ; 
 struct operand_data* odata ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
output_operand_data (void)
{
  struct operand_data *d;

  printf ("\nstatic const struct insn_operand_data operand_data[] = \n{\n");

  for (d = odata; d; d = d->next)
    {
      printf ("  {\n");

      printf ("    %s,\n",
	      d->predicate && d->predicate[0] ? d->predicate : "0");

      printf ("    \"%s\",\n", d->constraint ? d->constraint : "");

      printf ("    %smode,\n", GET_MODE_NAME (d->mode));

      printf ("    %d,\n", d->strict_low);

      printf ("    %d\n", d->eliminable);

      printf("  },\n");
    }
  printf("};\n\n\n");
}