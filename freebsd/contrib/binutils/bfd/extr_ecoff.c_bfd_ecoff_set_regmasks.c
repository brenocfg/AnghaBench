#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long gprmask; unsigned long fprmask; unsigned long* cprmask; } ;
typedef  TYPE_1__ ecoff_data_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_format (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_object ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_ecoff_flavour ; 
 TYPE_1__* ecoff_data (int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_ecoff_set_regmasks (bfd *abfd,
			unsigned long gprmask,
			unsigned long fprmask,
			unsigned long *cprmask)
{
  ecoff_data_type *tdata;

  if (bfd_get_flavour (abfd) != bfd_target_ecoff_flavour
      || bfd_get_format (abfd) != bfd_object)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  tdata = ecoff_data (abfd);
  tdata->gprmask = gprmask;
  tdata->fprmask = fprmask;
  if (cprmask != NULL)
    {
      int i;

      for (i = 0; i < 3; i++)
	tdata->cprmask[i] = cprmask[i];
    }

  return TRUE;
}