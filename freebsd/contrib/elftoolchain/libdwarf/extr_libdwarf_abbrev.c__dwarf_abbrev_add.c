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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint64_t ;
struct _Dwarf_Abbrev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  ab_attrdef; scalar_t__ ab_atnum; scalar_t__ ab_length; void* ab_offset; int /*<<< orphan*/  ab_children; void* ab_tag; void* ab_entry; } ;
struct TYPE_7__ {int /*<<< orphan*/  cu_abbrev_hash; int /*<<< orphan*/ * cu_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_1__* Dwarf_CU ;
typedef  TYPE_2__* Dwarf_Abbrev ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  HASH_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ab_entry ; 
 int /*<<< orphan*/  ab_hh ; 
 TYPE_2__* malloc (int) ; 

int
_dwarf_abbrev_add(Dwarf_CU cu, uint64_t entry, uint64_t tag, uint8_t children,
    uint64_t aboff, Dwarf_Abbrev *abp, Dwarf_Error *error)
{
	Dwarf_Abbrev ab;
	Dwarf_Debug dbg;

	dbg = cu != NULL ? cu->cu_dbg : NULL;

	if ((ab = malloc(sizeof(struct _Dwarf_Abbrev))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	/* Initialise the abbrev structure. */
	ab->ab_entry	= entry;
	ab->ab_tag	= tag;
	ab->ab_children	= children;
	ab->ab_offset	= aboff;
	ab->ab_length	= 0;	/* fill in later. */
	ab->ab_atnum	= 0;	/* fill in later. */

	/* Initialise the list of attribute definitions. */
	STAILQ_INIT(&ab->ab_attrdef);

	/* Add the abbrev to the hash table of the compilation unit. */
	if (cu != NULL)
		HASH_ADD(ab_hh, cu->cu_abbrev_hash, ab_entry,
		    sizeof(ab->ab_entry), ab);

	if (abp != NULL)
		*abp = ab;

	return (DW_DLE_NONE);
}