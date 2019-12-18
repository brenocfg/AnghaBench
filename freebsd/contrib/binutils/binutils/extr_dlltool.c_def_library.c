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
 int /*<<< orphan*/  _ (char*) ; 
 int d_is_dll ; 
 scalar_t__ d_is_exe ; 
 int /*<<< orphan*/  dll_name ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dll_name_from_def (char const*) ; 

void
def_library (const char *name, int base)
{
  /* xgettext:c-format */
  inform (_("LIBRARY: %s base: %x"), name, base);

  if (d_is_exe)
    non_fatal (_("Can't have LIBRARY and NAME"));

  /* If --dllname not provided, use the one in the DEF file.  */
  if (! dll_name)
    set_dll_name_from_def (name);
  d_is_dll = 1;
}