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
typedef  void* uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  cu_dbg; } ;
struct TYPE_6__ {int /*<<< orphan*/  die_dbg; TYPE_2__* die_cu; int /*<<< orphan*/ * die_ab; void* die_abnum; void* die_offset; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  TYPE_2__* Dwarf_CU ;
typedef  int /*<<< orphan*/ * Dwarf_Abbrev ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 int _dwarf_die_alloc (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_dwarf_die_add(Dwarf_CU cu, uint64_t offset, uint64_t abnum, Dwarf_Abbrev ab,
    Dwarf_Die *diep, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	Dwarf_Die die;
	int ret;

	assert(cu != NULL);
	assert(ab != NULL);

	dbg = cu->cu_dbg;

	if ((ret = _dwarf_die_alloc(dbg, &die, error)) != DW_DLE_NONE)
		return (ret);

	die->die_offset	= offset;
	die->die_abnum	= abnum;
	die->die_ab	= ab;
	die->die_cu	= cu;
	die->die_dbg	= cu->cu_dbg;

	if (diep != NULL)
		*diep = die;

	return (DW_DLE_NONE);
}