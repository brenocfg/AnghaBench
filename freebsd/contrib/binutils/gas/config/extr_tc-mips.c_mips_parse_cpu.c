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
struct mips_cpu_info {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ ABI_NEEDS_32BIT_REGS (int /*<<< orphan*/ ) ; 
 scalar_t__ ABI_NEEDS_64BIT_REGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISA_MIPS1 ; 
 int /*<<< orphan*/  ISA_MIPS3 ; 
 scalar_t__ MIPS_DEFAULT_64BIT ; 
 int /*<<< orphan*/  as_bad (char*,char const*,char const*) ; 
 scalar_t__ file_mips_gp32 ; 
 int /*<<< orphan*/  mips_abi ; 
 struct mips_cpu_info const* mips_cpu_info_from_isa (int /*<<< orphan*/ ) ; 
 struct mips_cpu_info* mips_cpu_info_table ; 
 scalar_t__ mips_matching_cpu_name_p (scalar_t__,char const*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static const struct mips_cpu_info *
mips_parse_cpu (const char *option, const char *cpu_string)
{
  const struct mips_cpu_info *p;

  /* 'from-abi' selects the most compatible architecture for the given
     ABI: MIPS I for 32-bit ABIs and MIPS III for 64-bit ABIs.  For the
     EABIs, we have to decide whether we're using the 32-bit or 64-bit
     version.  Look first at the -mgp options, if given, otherwise base
     the choice on MIPS_DEFAULT_64BIT.

     Treat NO_ABI like the EABIs.  One reason to do this is that the
     plain 'mips' and 'mips64' configs have 'from-abi' as their default
     architecture.  This code picks MIPS I for 'mips' and MIPS III for
     'mips64', just as we did in the days before 'from-abi'.  */
  if (strcasecmp (cpu_string, "from-abi") == 0)
    {
      if (ABI_NEEDS_32BIT_REGS (mips_abi))
	return mips_cpu_info_from_isa (ISA_MIPS1);

      if (ABI_NEEDS_64BIT_REGS (mips_abi))
	return mips_cpu_info_from_isa (ISA_MIPS3);

      if (file_mips_gp32 >= 0)
	return mips_cpu_info_from_isa (file_mips_gp32 ? ISA_MIPS1 : ISA_MIPS3);

      return mips_cpu_info_from_isa (MIPS_DEFAULT_64BIT
				     ? ISA_MIPS3
				     : ISA_MIPS1);
    }

  /* 'default' has traditionally been a no-op.  Probably not very useful.  */
  if (strcasecmp (cpu_string, "default") == 0)
    return 0;

  for (p = mips_cpu_info_table; p->name != 0; p++)
    if (mips_matching_cpu_name_p (p->name, cpu_string))
      return p;

  as_bad ("Bad value (%s) for %s", cpu_string, option);
  return 0;
}