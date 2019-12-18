#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct relocation_info {int dummy; } ;
typedef  TYPE_1__* sec_ptr ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_8__ {int a_drsize; int a_trsize; } ;
struct TYPE_7__ {int flags; int reloc_count; } ;

/* Variables and functions */
 int SEC_CONSTRUCTOR ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_get_format (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_object ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_5__* exec_hdr (int /*<<< orphan*/ *) ; 
 TYPE_1__* obj_bsssec (int /*<<< orphan*/ *) ; 
 TYPE_1__* obj_datasec (int /*<<< orphan*/ *) ; 
 TYPE_1__* obj_textsec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long
b_out_get_reloc_upper_bound (bfd *abfd, sec_ptr asect)
{
  if (bfd_get_format (abfd) != bfd_object)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  if (asect->flags & SEC_CONSTRUCTOR)
    return sizeof (arelent *) * (asect->reloc_count + 1);

  if (asect == obj_datasec (abfd))
    return (sizeof (arelent *) *
	    ((exec_hdr (abfd)->a_drsize / sizeof (struct relocation_info))
	     + 1));

  if (asect == obj_textsec (abfd))
    return (sizeof (arelent *) *
	    ((exec_hdr (abfd)->a_trsize / sizeof (struct relocation_info))
	     + 1));

  if (asect == obj_bsssec (abfd))
    return 0;

  bfd_set_error (bfd_error_invalid_operation);
  return -1;
}