#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sec_ptr ;
struct TYPE_5__ {scalar_t__ format; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  asymbol ;
typedef  int /*<<< orphan*/  arelent ;

/* Variables and functions */
 long BFD_SEND (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _bfd_canonicalize_reloc ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 scalar_t__ bfd_object ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 

long
bfd_canonicalize_reloc (bfd *abfd,
			sec_ptr asect,
			arelent **location,
			asymbol **symbols)
{
  if (abfd->format != bfd_object)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  return BFD_SEND (abfd, _bfd_canonicalize_reloc,
		   (abfd, asect, location, symbols));
}