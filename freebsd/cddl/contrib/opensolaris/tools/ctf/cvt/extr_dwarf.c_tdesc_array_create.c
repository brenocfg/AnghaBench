#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int t_size; int /*<<< orphan*/  t_flags; TYPE_2__* t_ardef; int /*<<< orphan*/  t_type; int /*<<< orphan*/  t_id; } ;
typedef  TYPE_1__ tdesc_t ;
typedef  int /*<<< orphan*/  dwarf_t ;
struct TYPE_6__ {int ad_nelems; TYPE_1__* ad_contents; int /*<<< orphan*/  ad_idxtype; } ;
typedef  TYPE_2__ ardef_t ;
typedef  void* Dwarf_Unsigned ;
typedef  void* Dwarf_Signed ;
typedef  int /*<<< orphan*/ * Dwarf_Die ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY ; 
 int /*<<< orphan*/  DW_AT_count ; 
 int /*<<< orphan*/  DW_AT_upper_bound ; 
 scalar_t__ DW_TAG_subrange_type ; 
 int /*<<< orphan*/  TDESC_F_RESOLVED ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_off (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * die_sibling (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ die_signed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ die_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ die_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfgtid_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdesc_intr_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminate (char*,int /*<<< orphan*/ ) ; 
 void* xcalloc (int) ; 

__attribute__((used)) static void
tdesc_array_create(dwarf_t *dw, Dwarf_Die dim, tdesc_t *arrtdp,
    tdesc_t *dimtdp)
{
	Dwarf_Unsigned uval;
	Dwarf_Signed sval;
	tdesc_t *ctdp = NULL;
	Dwarf_Die dim2;
	ardef_t *ar;

	if ((dim2 = die_sibling(dw, dim)) == NULL) {
		ctdp = arrtdp;
	} else if (die_tag(dw, dim2) == DW_TAG_subrange_type) {
		ctdp = xcalloc(sizeof (tdesc_t));
		ctdp->t_id = mfgtid_next(dw);
		debug(3, "die %llu: creating new type %u for sub-dimension\n",
		    die_off(dw, dim2), ctdp->t_id);
		tdesc_array_create(dw, dim2, arrtdp, ctdp);
	} else {
		terminate("die %llu: unexpected non-subrange node in array\n",
		    die_off(dw, dim2));
	}

	dimtdp->t_type = ARRAY;
	dimtdp->t_ardef = ar = xcalloc(sizeof (ardef_t));

	/*
	 * Array bounds can be signed or unsigned, but there are several kinds
	 * of signless forms (data1, data2, etc) that take their sign from the
	 * routine that is trying to interpret them.  That is, data1 can be
	 * either signed or unsigned, depending on whether you use the signed or
	 * unsigned accessor function.  GCC will use the signless forms to store
	 * unsigned values which have their high bit set, so we need to try to
	 * read them first as unsigned to get positive values.  We could also
	 * try signed first, falling back to unsigned if we got a negative
	 * value.
	 */
	if (die_unsigned(dw, dim, DW_AT_upper_bound, &uval, 0))
		ar->ad_nelems = uval + 1;
	else if (die_signed(dw, dim, DW_AT_upper_bound, &sval, 0))
		ar->ad_nelems = sval + 1;
	else if (die_unsigned(dw, dim, DW_AT_count, &uval, 0))
		ar->ad_nelems = uval;
	else if (die_signed(dw, dim, DW_AT_count, &sval, 0))
		ar->ad_nelems = sval;
	else
		ar->ad_nelems = 0;

	/*
	 * Different compilers use different index types.  Force the type to be
	 * a common, known value (long).
	 */
	ar->ad_idxtype = tdesc_intr_long(dw);
	ar->ad_contents = ctdp;

	if (ar->ad_contents->t_size != 0) {
		dimtdp->t_size = ar->ad_contents->t_size * ar->ad_nelems;
		dimtdp->t_flags |= TDESC_F_RESOLVED;
	}
}