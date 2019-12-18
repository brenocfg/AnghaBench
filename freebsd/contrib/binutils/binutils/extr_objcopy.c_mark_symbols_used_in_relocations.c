#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  TYPE_2__* sec_ptr ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_16__ {TYPE_1__** sym_ptr_ptr; } ;
typedef  TYPE_3__ arelent ;
struct TYPE_18__ {TYPE_1__* symbol; } ;
struct TYPE_17__ {TYPE_1__* symbol; } ;
struct TYPE_15__ {int /*<<< orphan*/ * output_section; } ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {TYPE_1__* symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_KEEP ; 
 TYPE_12__* bfd_abs_section_ptr ; 
 long bfd_canonicalize_reloc (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__**,int /*<<< orphan*/ **) ; 
 TYPE_9__* bfd_com_section_ptr ; 
 scalar_t__ bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 long bfd_get_reloc_upper_bound (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_7__* bfd_und_section_ptr ; 
 int /*<<< orphan*/  free (TYPE_3__**) ; 
 TYPE_3__** xmalloc (long) ; 

__attribute__((used)) static void
mark_symbols_used_in_relocations (bfd *ibfd, sec_ptr isection, void *symbolsarg)
{
  asymbol **symbols = symbolsarg;
  long relsize;
  arelent **relpp;
  long relcount, i;

  /* Ignore an input section with no corresponding output section.  */
  if (isection->output_section == NULL)
    return;

  relsize = bfd_get_reloc_upper_bound (ibfd, isection);
  if (relsize < 0)
    {
      /* Do not complain if the target does not support relocations.  */
      if (relsize == -1 && bfd_get_error () == bfd_error_invalid_operation)
	return;
      bfd_fatal (bfd_get_filename (ibfd));
    }

  if (relsize == 0)
    return;

  relpp = xmalloc (relsize);
  relcount = bfd_canonicalize_reloc (ibfd, isection, relpp, symbols);
  if (relcount < 0)
    bfd_fatal (bfd_get_filename (ibfd));

  /* Examine each symbol used in a relocation.  If it's not one of the
     special bfd section symbols, then mark it with BSF_KEEP.  */
  for (i = 0; i < relcount; i++)
    {
      if (*relpp[i]->sym_ptr_ptr != bfd_com_section_ptr->symbol
	  && *relpp[i]->sym_ptr_ptr != bfd_abs_section_ptr->symbol
	  && *relpp[i]->sym_ptr_ptr != bfd_und_section_ptr->symbol)
	(*relpp[i]->sym_ptr_ptr)->flags |= BSF_KEEP;
    }

  if (relpp != NULL)
    free (relpp);
}