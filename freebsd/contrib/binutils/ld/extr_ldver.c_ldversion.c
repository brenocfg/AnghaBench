#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* emulation_name; } ;
typedef  TYPE_1__ ld_emulation_xfer_type ;

/* Variables and functions */
 char* BFD_VERSION_STRING ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_1__** ld_emulations ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

void
ldversion (int noisy)
{
  /* Output for noisy == 2 is intended to follow the GNU standards.  */
  fprintf (stdout, _("GNU ld %s\n"), BFD_VERSION_STRING);

  if (noisy & 2)
    {
      printf (_("Copyright 2007 Free Software Foundation, Inc.\n"));
      printf (_("\
This program is free software; you may redistribute it under the terms of\n\
the GNU General Public License.  This program has absolutely no warranty.\n"));
    }

  if (noisy & 1)
    {
      ld_emulation_xfer_type **ptr = ld_emulations;

      printf (_("  Supported emulations:\n"));
      while (*ptr)
	{
	  printf ("   %s\n", (*ptr)->emulation_name);
	  ptr++;
	}
    }
}