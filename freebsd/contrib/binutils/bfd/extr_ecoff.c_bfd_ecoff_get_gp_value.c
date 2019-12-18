#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  gp; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_format (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_object ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_ecoff_flavour ; 
 TYPE_1__* ecoff_data (int /*<<< orphan*/ *) ; 

bfd_vma
bfd_ecoff_get_gp_value (bfd *abfd)
{
  if (bfd_get_flavour (abfd) != bfd_target_ecoff_flavour
      || bfd_get_format (abfd) != bfd_object)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return 0;
    }

  return ecoff_data (abfd)->gp;
}