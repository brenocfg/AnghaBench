#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct internal_filehdr {int /*<<< orphan*/  f_symptr; } ;
struct internal_aouthdr {scalar_t__ magic; int /*<<< orphan*/  fprmask; int /*<<< orphan*/ * cprmask; int /*<<< orphan*/  gprmask; int /*<<< orphan*/  gp_value; scalar_t__ tsize; scalar_t__ text_start; } ;
struct TYPE_7__ {int gp_size; int /*<<< orphan*/  fprmask; int /*<<< orphan*/ * cprmask; int /*<<< orphan*/  gprmask; int /*<<< orphan*/  gp; scalar_t__ text_end; scalar_t__ text_start; int /*<<< orphan*/  sym_filepos; } ;
typedef  TYPE_1__ ecoff_data_type ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  D_PAGED ; 
 scalar_t__ ECOFF_AOUT_ZMAGIC ; 
 int /*<<< orphan*/  _bfd_ecoff_mkobject (TYPE_2__*) ; 
 TYPE_1__* ecoff_data (TYPE_2__*) ; 

void *
_bfd_ecoff_mkobject_hook (bfd *abfd, void * filehdr, void * aouthdr)
{
  struct internal_filehdr *internal_f = (struct internal_filehdr *) filehdr;
  struct internal_aouthdr *internal_a = (struct internal_aouthdr *) aouthdr;
  ecoff_data_type *ecoff;

  if (! _bfd_ecoff_mkobject (abfd))
    return NULL;

  ecoff = ecoff_data (abfd);
  ecoff->gp_size = 8;
  ecoff->sym_filepos = internal_f->f_symptr;

  if (internal_a != NULL)
    {
      int i;

      ecoff->text_start = internal_a->text_start;
      ecoff->text_end = internal_a->text_start + internal_a->tsize;
      ecoff->gp = internal_a->gp_value;
      ecoff->gprmask = internal_a->gprmask;
      for (i = 0; i < 4; i++)
	ecoff->cprmask[i] = internal_a->cprmask[i];
      ecoff->fprmask = internal_a->fprmask;
      if (internal_a->magic == ECOFF_AOUT_ZMAGIC)
	abfd->flags |= D_PAGED;
      else
	abfd->flags &=~ D_PAGED;
    }

  /* It turns out that no special action is required by the MIPS or
     Alpha ECOFF backends.  They have different information in the
     a.out header, but we just copy it all (e.g., gprmask, cprmask and
     fprmask) and let the swapping routines ensure that only relevant
     information is written out.  */

  return (void *) ecoff;
}