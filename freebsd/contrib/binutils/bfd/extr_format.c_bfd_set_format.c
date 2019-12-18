#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_format ;
typedef  int bfd_boolean ;
struct TYPE_6__ {scalar_t__ format; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_SEND_FMT (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  _bfd_set_format ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_read_p (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_type_end ; 
 scalar_t__ bfd_unknown ; 

bfd_boolean
bfd_set_format (bfd *abfd, bfd_format format)
{
  if (bfd_read_p (abfd)
      || (unsigned int) abfd->format >= (unsigned int) bfd_type_end)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  if (abfd->format != bfd_unknown)
    return abfd->format == format;

  /* Presume the answer is yes.  */
  abfd->format = format;

  if (!BFD_SEND_FMT (abfd, _bfd_set_format, (abfd)))
    {
      abfd->format = bfd_unknown;
      return FALSE;
    }

  return TRUE;
}