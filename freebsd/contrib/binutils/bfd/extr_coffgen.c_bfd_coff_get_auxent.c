#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ p; TYPE_10__* l; } ;
struct TYPE_23__ {TYPE_8__ x_scnlen; } ;
struct TYPE_18__ {scalar_t__ p; TYPE_10__* l; } ;
struct TYPE_19__ {TYPE_4__ x_endndx; } ;
struct TYPE_20__ {TYPE_5__ x_fcn; } ;
struct TYPE_17__ {scalar_t__ p; TYPE_10__* l; } ;
struct TYPE_21__ {TYPE_6__ x_fcnary; TYPE_3__ x_tagndx; } ;
union internal_auxent {TYPE_9__ x_csect; TYPE_7__ x_sym; } ;
struct TYPE_15__ {int n_numaux; } ;
struct TYPE_16__ {union internal_auxent auxent; TYPE_1__ syment; } ;
struct TYPE_13__ {scalar_t__ fix_scnlen; scalar_t__ fix_end; scalar_t__ fix_tag; TYPE_2__ u; } ;
typedef  TYPE_10__ combined_entry_type ;
struct TYPE_14__ {TYPE_10__* native; } ;
typedef  TYPE_11__ coff_symbol_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_error_invalid_operation ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 TYPE_11__* coff_symbol_from (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int obj_raw_syments (int /*<<< orphan*/ *) ; 

bfd_boolean
bfd_coff_get_auxent (bfd *abfd,
		     asymbol *symbol,
		     int indx,
		     union internal_auxent *pauxent)
{
  coff_symbol_type *csym;
  combined_entry_type *ent;

  csym = coff_symbol_from (abfd, symbol);

  if (csym == NULL
      || csym->native == NULL
      || indx >= csym->native->u.syment.n_numaux)
    {
      bfd_set_error (bfd_error_invalid_operation);
      return FALSE;
    }

  ent = csym->native + indx + 1;

  *pauxent = ent->u.auxent;

  if (ent->fix_tag)
    pauxent->x_sym.x_tagndx.l =
      ((combined_entry_type *) pauxent->x_sym.x_tagndx.p
       - obj_raw_syments (abfd));

  if (ent->fix_end)
    pauxent->x_sym.x_fcnary.x_fcn.x_endndx.l =
      ((combined_entry_type *) pauxent->x_sym.x_fcnary.x_fcn.x_endndx.p
       - obj_raw_syments (abfd));

  if (ent->fix_scnlen)
    pauxent->x_csect.x_scnlen.l =
      ((combined_entry_type *) pauxent->x_csect.x_scnlen.p
       - obj_raw_syments (abfd));

  return TRUE;
}