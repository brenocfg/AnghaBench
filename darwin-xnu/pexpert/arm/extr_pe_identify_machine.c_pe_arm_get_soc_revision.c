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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 scalar_t__ DTFindEntry (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ DTGetProperty (int /*<<< orphan*/ ,char*,void**,int*) ; 
 scalar_t__ kSuccess ; 

uint32_t
pe_arm_get_soc_revision(void)
{
	DTEntry		entryP;
	uint32_t	*value;
	uint32_t	size;

	if ((DTFindEntry("name", "arm-io", &entryP) == kSuccess) 
	    && (DTGetProperty(entryP, "chip-revision", (void **)&value, &size) == kSuccess)) {
		if (size == 8)
			return((uint32_t)*(unsigned long long *)value);
		else
			return(*value);
	}
	return 0;
}