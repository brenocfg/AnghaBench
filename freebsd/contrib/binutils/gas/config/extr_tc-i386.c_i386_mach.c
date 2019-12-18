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
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 unsigned long bfd_mach_i386_i386 ; 
 unsigned long bfd_mach_x86_64 ; 
 int /*<<< orphan*/  default_arch ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

unsigned long
i386_mach ()
{
  if (!strcmp (default_arch, "x86_64"))
    return bfd_mach_x86_64;
  else if (!strcmp (default_arch, "i386"))
    return bfd_mach_i386_i386;
  else
    as_fatal (_("Unknown architecture"));
}