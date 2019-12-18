#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct internal_ldhdr {int l_nreloc; } ;
struct external_ldhdr {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_9__ {int /*<<< orphan*/ * contents; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_xcoff_swap_ldhdr_in (TYPE_1__*,struct external_ldhdr*,struct internal_ldhdr*) ; 
 TYPE_3__* coff_section_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcoff_get_section_contents (TYPE_1__*,int /*<<< orphan*/ *) ; 

long
_bfd_xcoff_get_dynamic_reloc_upper_bound (bfd *abfd)
{
  asection *lsec;
  bfd_byte *contents;
  struct internal_ldhdr ldhdr;

  if ((abfd->flags & DYNAMIC) == 0)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return -1;
    }

  lsec = bfd_get_section_by_name (abfd, ".loader");
  if (lsec == NULL)
    {
      bfd_set_error (bfd_error_no_symbols);
      return -1;
    }

  if (! xcoff_get_section_contents (abfd, lsec))
    return -1;
  contents = coff_section_data (abfd, lsec)->contents;

  bfd_xcoff_swap_ldhdr_in (abfd, (struct external_ldhdr *) contents, &ldhdr);

  return (ldhdr.l_nreloc + 1) * sizeof (arelent *);
}