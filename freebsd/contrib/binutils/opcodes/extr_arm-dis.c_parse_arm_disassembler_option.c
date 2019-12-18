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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char*,char*) ; 
 int NUM_ARM_REGNAMES ; 
 char* _ (char*) ; 
 int force_thumb ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int regname_selected ; 
 TYPE_1__* regnames ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strneq (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
parse_arm_disassembler_option (char *option)
{
  if (option == NULL)
    return;

  if (CONST_STRNEQ (option, "reg-names-"))
    {
      int i;

      option += 10;

      for (i = NUM_ARM_REGNAMES; i--;)
	if (strneq (option, regnames[i].name, strlen (regnames[i].name)))
	  {
	    regname_selected = i;
	    break;
	  }

      if (i < 0)
	/* XXX - should break 'option' at following delimiter.  */
	fprintf (stderr, _("Unrecognised register name set: %s\n"), option);
    }
  else if (CONST_STRNEQ (option, "force-thumb"))
    force_thumb = 1;
  else if (CONST_STRNEQ (option, "no-force-thumb"))
    force_thumb = 0;
  else
    /* XXX - should break 'option' at following delimiter.  */
    fprintf (stderr, _("Unrecognised disassembler option: %s\n"), option);

  return;
}