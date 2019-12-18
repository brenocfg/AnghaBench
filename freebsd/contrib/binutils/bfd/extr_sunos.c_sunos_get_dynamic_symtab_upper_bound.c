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
struct sunos_dynamic_info {int dynsym_count; int /*<<< orphan*/  valid; } ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ obj_aout_dynamic_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunos_read_dynamic_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
sunos_get_dynamic_symtab_upper_bound (bfd *abfd)
{
  struct sunos_dynamic_info *info;

  if (! sunos_read_dynamic_info (abfd))
    return -1;

  info = (struct sunos_dynamic_info *) obj_aout_dynamic_info (abfd);
  if (! info->valid)
    {
      bfd_set_error (bfd_error_no_symbols);
      return -1;
    }

  return (info->dynsym_count + 1) * sizeof (asymbol *);
}