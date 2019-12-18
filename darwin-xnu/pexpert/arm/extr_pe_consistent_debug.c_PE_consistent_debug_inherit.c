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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dbg_registry_t ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 scalar_t__ DTGetProperty (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ DTLookupEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * consistent_debug_registry ; 
 scalar_t__ kSuccess ; 
 scalar_t__ ml_map_high_window (uintptr_t,int) ; 

int PE_consistent_debug_inherit(void)
{
	DTEntry		entryP;
	uintptr_t	*prop_data;
	uintptr_t	root_pointer = 0;
	uint32_t	size;

        if ((DTLookupEntry(NULL, "/chosen", &entryP) == kSuccess))
		if (DTGetProperty(entryP, "consistent-debug-root", (void **)&prop_data, &size) == kSuccess)
			root_pointer = prop_data[0];
	if (root_pointer == 0)
		return -1;
	consistent_debug_registry = (dbg_registry_t *)ml_map_high_window(root_pointer, sizeof(dbg_registry_t));
	return 0;
}