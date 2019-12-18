#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int _dwarf_write_uleb128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 

int
_dwarf_write_uleb128_alloc(uint8_t **block, uint64_t *size, uint64_t *offsetp,
    uint64_t val, Dwarf_Error *error)
{
	int len;

	assert(*size > 0);

	while ((len = _dwarf_write_uleb128(*block + *offsetp, *block + *size,
	    val)) < 0) {
		*size *= 2;
		*block = realloc(*block, (size_t) *size);
		if (*block == NULL) {
			DWARF_SET_ERROR(NULL, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}
	}

	*offsetp += len;

	return (DW_DLE_NONE);
}