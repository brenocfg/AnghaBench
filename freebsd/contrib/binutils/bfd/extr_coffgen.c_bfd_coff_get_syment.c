#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct internal_syment {scalar_t__ n_value; } ;
struct TYPE_7__ {TYPE_2__* native; } ;
typedef  TYPE_3__ coff_symbol_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_5__ {struct internal_syment syment; } ;
struct TYPE_6__ {scalar_t__ fix_value; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_3__* coff_symbol_from (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ obj_raw_syments (int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_coff_get_syment (bfd *abfd,
		     asymbol *symbol,
		     struct internal_syment *psyment)
{
  coff_symbol_type *csym;

  csym = coff_symbol_from (abfd, symbol);
  if (csym == NULL || csym->native == NULL)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  *psyment = csym->native->u.syment;

  if (csym->native->fix_value)
    psyment->n_value = psyment->n_value -
      (unsigned long) obj_raw_syments (abfd);

  /* FIXME: We should handle fix_line here.  */

  return TRUE;
}