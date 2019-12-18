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
struct bfd_arch_info {int arch; } ;
typedef  enum bfd_architecture { ____Placeholder_bfd_architecture } bfd_architecture ;

/* Variables and functions */
 struct bfd_arch_info* TARGET_ARCHITECTURE ; 
 int bfd_get_arch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/ * exec_bfd ; 

__attribute__((used)) static enum bfd_architecture
default_gcore_arch (void)
{
#ifdef TARGET_ARCHITECTURE
  const struct bfd_arch_info * bfdarch = TARGET_ARCHITECTURE;

  if (bfdarch != NULL)
    return bfdarch->arch;
#endif
  if (exec_bfd == NULL)
    error ("Can't find bfd architecture for corefile (need execfile).");

  return bfd_get_arch (exec_bfd);
}