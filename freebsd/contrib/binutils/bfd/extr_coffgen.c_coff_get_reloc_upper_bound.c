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
typedef  TYPE_1__* sec_ptr ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_3__ {int reloc_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_get_format (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_object ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 

long
coff_get_reloc_upper_bound (bfd *abfd, sec_ptr asect)
{
  if (bfd_get_format (abfd) != bfd_object)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }
  return (asect->reloc_count + 1) * sizeof (arelent *);
}