#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_Attribute {int dummy; } ;
struct TYPE_14__ {scalar_t__ at_attrib; int at_form; TYPE_1__* u; } ;
struct TYPE_13__ {int /*<<< orphan*/  die_name; int /*<<< orphan*/  die_attr; } ;
struct TYPE_12__ {int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Die ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 scalar_t__ DW_AT_name ; 
 int DW_DLE_NONE ; 
#define  DW_FORM_string 129 
#define  DW_FORM_strp 128 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int _dwarf_attr_alloc (TYPE_2__*,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  at_next ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

__attribute__((used)) static int
_dwarf_attr_add(Dwarf_Die die, Dwarf_Attribute atref, Dwarf_Attribute *atp,
    Dwarf_Error *error)
{
	Dwarf_Attribute at;
	int ret;

	if ((ret = _dwarf_attr_alloc(die, &at, error)) != DW_DLE_NONE)
		return (ret);

	memcpy(at, atref, sizeof(struct _Dwarf_Attribute));

	STAILQ_INSERT_TAIL(&die->die_attr, at, at_next);

	/* Save a pointer to the attribute name if this is one. */
	if (at->at_attrib == DW_AT_name) {
		switch (at->at_form) {
		case DW_FORM_strp:
			die->die_name = at->u[1].s;
			break;
		case DW_FORM_string:
			die->die_name = at->u[0].s;
			break;
		default:
			break;
		}
	}

	if (atp != NULL)
		*atp = at;

	return (DW_DLE_NONE);
}