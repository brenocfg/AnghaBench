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
 char* TARGET_ALIAS ; 
 char* VERSION ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void
print_version_id (void)
{
  static int printed;

  if (printed)
    return;
  printed = 1;

  fprintf (stderr, _("GNU assembler version %s (%s) using BFD version %s\n"),
	   VERSION, TARGET_ALIAS, BFD_VERSION_STRING);
}