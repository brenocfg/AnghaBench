#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sec_ptr ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_6__ {scalar_t__ output_has_begun; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 

bfd_boolean
bfd_set_section_size (bfd *abfd, sec_ptr ptr, bfd_size_type val)
{
  /* Once you've started writing to any section you cannot create or change
     the size of any others.  */

  if (abfd->output_has_begun)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  ptr->size = val;
  return TRUE;
}