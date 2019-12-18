#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  emulation_name; } ;
typedef  TYPE_1__ ld_emulation_xfer_type ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  einfo (char*,...) ; 
 TYPE_1__* ld_emulation ; 
 TYPE_1__** ld_emulations ; 
 int /*<<< orphan*/  ldemul_list_emulations (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
ldemul_choose_mode (char *target)
{
  ld_emulation_xfer_type **eptr = ld_emulations;
  /* Ignore "gld" prefix.  */
  if (target[0] == 'g' && target[1] == 'l' && target[2] == 'd')
    target += 3;
  for (; *eptr; eptr++)
    {
      if (strcmp (target, (*eptr)->emulation_name) == 0)
	{
	  ld_emulation = *eptr;
	  return;
	}
    }
  einfo (_("%P: unrecognised emulation mode: %s\n"), target);
  einfo (_("Supported emulations: "));
  ldemul_list_emulations (stderr);
  einfo ("%F\n");
}