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
 char* _ (char*) ; 
 int print_width ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ undefined_only ; 

__attribute__((used)) static void
print_object_filename_sysv (char *filename)
{
  if (undefined_only)
    printf (_("\n\nUndefined symbols from %s:\n\n"), filename);
  else
    printf (_("\n\nSymbols from %s:\n\n"), filename);
  if (print_width == 32)
    printf (_("\
Name                  Value   Class        Type         Size     Line  Section\n\n"));
  else
    printf (_("\
Name                  Value           Class        Type         Size             Line  Section\n\n"));
}