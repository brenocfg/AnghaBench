#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_4__ {size_t dbg_strtab_size; size_t dbg_strtab_cap; char* dbg_strtab; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 char* realloc (char*,size_t) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

int
_dwarf_strtab_add(Dwarf_Debug dbg, char *string, uint64_t *off,
    Dwarf_Error *error)
{
	size_t len;

	assert(dbg != NULL && string != NULL);

	len = strlen(string) + 1;
	while (dbg->dbg_strtab_size + len > dbg->dbg_strtab_cap) {
		dbg->dbg_strtab_cap *= 2;
		dbg->dbg_strtab = realloc(dbg->dbg_strtab,
		    (size_t) dbg->dbg_strtab_cap);
		if (dbg->dbg_strtab == NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}
	}

	if (off != NULL)
		*off = dbg->dbg_strtab_size;

	strncpy(&dbg->dbg_strtab[dbg->dbg_strtab_size], string, len - 1);
	dbg->dbg_strtab_size += len;
	dbg->dbg_strtab[dbg->dbg_strtab_size - 1] = '\0';

	return (DW_DLE_NONE);
}