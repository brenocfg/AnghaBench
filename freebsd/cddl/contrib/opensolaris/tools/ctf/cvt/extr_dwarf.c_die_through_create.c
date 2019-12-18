#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int t_type; int /*<<< orphan*/  t_name; int /*<<< orphan*/  t_flags; int /*<<< orphan*/  t_size; int /*<<< orphan*/  t_tdesc; } ;
typedef  TYPE_2__ tdesc_t ;
struct TYPE_14__ {TYPE_2__* ii_dtype; int /*<<< orphan*/  ii_name; int /*<<< orphan*/  ii_type; } ;
typedef  TYPE_3__ iidesc_t ;
struct TYPE_15__ {TYPE_1__* dw_td; int /*<<< orphan*/  dw_ptrsz; } ;
typedef  TYPE_4__ dwarf_t ;
struct TYPE_12__ {int /*<<< orphan*/  td_iihash; } ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_type ; 
 int /*<<< orphan*/  II_TYPE ; 
 int POINTER ; 
 int /*<<< orphan*/  TDESC_F_RESOLVED ; 
 int TYPEDEF ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * die_attr (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_lookup_pass1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iidesc_add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  tdesc_intr_void (TYPE_4__*) ; 
 TYPE_3__* xcalloc (int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
die_through_create(dwarf_t *dw, Dwarf_Die die, Dwarf_Off off, tdesc_t *tdp,
    int type, const char *typename)
{
	Dwarf_Attribute attr;

	debug(3, "die %llu <%llx>: creating %s type %d\n", off, off, typename, type);

	tdp->t_type = type;

	if ((attr = die_attr(dw, die, DW_AT_type, 0)) != NULL) {
		tdp->t_tdesc = die_lookup_pass1(dw, die, DW_AT_type);
	} else {
		tdp->t_tdesc = tdesc_intr_void(dw);
	}

	if (type == POINTER)
		tdp->t_size = dw->dw_ptrsz;

	tdp->t_flags |= TDESC_F_RESOLVED;

	if (type == TYPEDEF) {
		iidesc_t *ii = xcalloc(sizeof (iidesc_t));
		ii->ii_type = II_TYPE;
		ii->ii_name = xstrdup(tdp->t_name);
		ii->ii_dtype = tdp;

		iidesc_add(dw->dw_td->td_iihash, ii);
	}
}