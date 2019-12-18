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
typedef  enum mips_abi { ____Placeholder_mips_abi } mips_abi ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int MIPS_ABI_EABI32 ; 
 int MIPS_ABI_EABI64 ; 
 int MIPS_ABI_N32 ; 
 int MIPS_ABI_N64 ; 
 int MIPS_ABI_O32 ; 
 int MIPS_ABI_O64 ; 
 int MIPS_ABI_UNKNOWN ; 
 char* bfd_get_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 

__attribute__((used)) static void
mips_find_abi_section (bfd *abfd, asection *sect, void *obj)
{
  enum mips_abi *abip = (enum mips_abi *) obj;
  const char *name = bfd_get_section_name (abfd, sect);

  if (*abip != MIPS_ABI_UNKNOWN)
    return;

  if (strncmp (name, ".mdebug.", 8) != 0)
    return;

  if (strcmp (name, ".mdebug.abi32") == 0)
    *abip = MIPS_ABI_O32;
  else if (strcmp (name, ".mdebug.abiN32") == 0)
    *abip = MIPS_ABI_N32;
  else if (strcmp (name, ".mdebug.abi64") == 0)
    *abip = MIPS_ABI_N64;
  else if (strcmp (name, ".mdebug.abiO64") == 0)
    *abip = MIPS_ABI_O64;
  else if (strcmp (name, ".mdebug.eabi32") == 0)
    *abip = MIPS_ABI_EABI32;
  else if (strcmp (name, ".mdebug.eabi64") == 0)
    *abip = MIPS_ABI_EABI64;
  else
    warning ("unsupported ABI %s.", name + 8);
}