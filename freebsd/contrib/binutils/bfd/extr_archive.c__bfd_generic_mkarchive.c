#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct artdata {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_6__ {int /*<<< orphan*/  aout_ar_data; } ;
struct TYPE_7__ {TYPE_1__ tdata; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * bfd_ardata (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_zalloc (TYPE_2__*,int) ; 

bfd_boolean
_bfd_generic_mkarchive (bfd *abfd)
{
  bfd_size_type amt = sizeof (struct artdata);

  abfd->tdata.aout_ar_data = bfd_zalloc (abfd, amt);
  if (bfd_ardata (abfd) == NULL)
    return FALSE;

  /* Already cleared by bfd_zalloc above.
     bfd_ardata (abfd)->cache = NULL;
     bfd_ardata (abfd)->archive_head = NULL;
     bfd_ardata (abfd)->symdefs = NULL;
     bfd_ardata (abfd)->extended_names = NULL;
     bfd_ardata (abfd)->extended_names_size = 0;
     bfd_ardata (abfd)->tdata = NULL;  */

  return TRUE;
}