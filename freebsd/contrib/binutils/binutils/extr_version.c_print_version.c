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
 char* BFD_VERSION_STRING ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
print_version (const char *name)
{
  /* This output is intended to follow the GNU standards document.  */
  /* xgettext:c-format */
  printf ("GNU %s %s\n", name, BFD_VERSION_STRING);
  printf (_("Copyright 2007 Free Software Foundation, Inc.\n"));
  printf (_("\
This program is free software; you may redistribute it under the terms of\n\
the GNU General Public License.  This program has absolutely no warranty.\n"));
  exit (0);
}