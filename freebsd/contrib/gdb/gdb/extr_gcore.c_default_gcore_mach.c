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
struct bfd_arch_info {unsigned long mach; } ;

/* Variables and functions */
 struct bfd_arch_info* TARGET_ARCHITECTURE ; 
 unsigned long bfd_get_mach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * exec_bfd ; 

__attribute__((used)) static unsigned long
default_gcore_mach (void)
{
#if 1	/* See if this even matters...  */
  return 0;
#else
#ifdef TARGET_ARCHITECTURE
  const struct bfd_arch_info *bfdarch = TARGET_ARCHITECTURE;

  if (bfdarch != NULL)
    return bfdarch->mach;
#endif /* TARGET_ARCHITECTURE */
  if (exec_bfd == NULL)
    error ("Can't find default bfd machine type (need execfile).");

  return bfd_get_mach (exec_bfd);
#endif /* 1 */
}