#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int /*<<< orphan*/  description; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NUM_ARM_REGNAMES ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__* regnames ; 
 int strlen (char*) ; 

void
print_arm_disassembler_options (FILE *stream)
{
  int i;

  fprintf (stream, _("\n\
The following ARM specific disassembler options are supported for use with\n\
the -M switch:\n"));

  for (i = NUM_ARM_REGNAMES; i--;)
    fprintf (stream, "  reg-names-%s %*c%s\n",
	     regnames[i].name,
	     (int)(14 - strlen (regnames[i].name)), ' ',
	     regnames[i].description);

  fprintf (stream, "  force-thumb              Assume all insns are Thumb insns\n");
  fprintf (stream, "  no-force-thumb           Examine preceeding label to determine an insn's type\n\n");
}