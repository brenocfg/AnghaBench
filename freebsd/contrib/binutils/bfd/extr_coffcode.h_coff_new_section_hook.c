#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  n_sclass; int /*<<< orphan*/  n_type; } ;
struct TYPE_12__ {TYPE_1__ syment; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
typedef  TYPE_3__ combined_entry_type ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_14__ {int /*<<< orphan*/  symbol; scalar_t__ alignment_power; } ;
typedef  TYPE_4__ asection ;
struct TYPE_15__ {TYPE_3__* native; } ;

/* Variables and functions */
 scalar_t__ COFF_DEFAULT_SECTION_ALIGNMENT_POWER ; 
 int /*<<< orphan*/  C_STAT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  T_NULL ; 
 int /*<<< orphan*/  _bfd_generic_new_section_hook (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  bfd_get_section_name (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ bfd_xcoff_data_align_power (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_xcoff_text_align_power (int /*<<< orphan*/ *) ; 
 TYPE_3__* bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  coff_section_alignment_table ; 
 int /*<<< orphan*/  coff_section_alignment_table_size ; 
 int /*<<< orphan*/  coff_set_custom_section_alignment (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* coffsymbol (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bfd_boolean
coff_new_section_hook (bfd * abfd, asection * section)
{
  combined_entry_type *native;
  bfd_size_type amt;

  section->alignment_power = COFF_DEFAULT_SECTION_ALIGNMENT_POWER;

#ifdef RS6000COFF_C
  if (bfd_xcoff_text_align_power (abfd) != 0
      && strcmp (bfd_get_section_name (abfd, section), ".text") == 0)
    section->alignment_power = bfd_xcoff_text_align_power (abfd);
  if (bfd_xcoff_data_align_power (abfd) != 0
      && strcmp (bfd_get_section_name (abfd, section), ".data") == 0)
    section->alignment_power = bfd_xcoff_data_align_power (abfd);
#endif

  /* Set up the section symbol.  */
  if (!_bfd_generic_new_section_hook (abfd, section))
    return FALSE;

  /* Allocate aux records for section symbols, to store size and
     related info.

     @@ The 10 is a guess at a plausible maximum number of aux entries
     (but shouldn't be a constant).  */
  amt = sizeof (combined_entry_type) * 10;
  native = bfd_zalloc (abfd, amt);
  if (native == NULL)
    return FALSE;

  /* We don't need to set up n_name, n_value, or n_scnum in the native
     symbol information, since they'll be overridden by the BFD symbol
     anyhow.  However, we do need to set the type and storage class,
     in case this symbol winds up getting written out.  The value 0
     for n_numaux is already correct.  */

  native->u.syment.n_type = T_NULL;
  native->u.syment.n_sclass = C_STAT;

  coffsymbol (section->symbol)->native = native;

  coff_set_custom_section_alignment (abfd, section,
				     coff_section_alignment_table,
				     coff_section_alignment_table_size);

  return TRUE;
}