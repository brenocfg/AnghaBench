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
typedef  uintptr_t vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 scalar_t__ DTFindEntry (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DTGetProperty (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOC_DEVICE_TYPE_BUFFER_SIZE ; 
 uintptr_t gPESoCBasePhys ; 
 scalar_t__ gPESoCDeviceType ; 
 scalar_t__ gPESoCDeviceTypeBuffer ; 
 scalar_t__ kSuccess ; 
 int /*<<< orphan*/  strlcpy (scalar_t__,char*,int /*<<< orphan*/ ) ; 

vm_offset_t
pe_arm_get_soc_base_phys(void)
{
	DTEntry		entryP;
	uintptr_t 	*ranges_prop;
	uint32_t	prop_size;
	char           *tmpStr;

	if (DTFindEntry("name", "arm-io", &entryP) == kSuccess) {
		if (gPESoCDeviceType == 0) {
			DTGetProperty(entryP, "device_type", (void **)&tmpStr, &prop_size);
			strlcpy(gPESoCDeviceTypeBuffer, tmpStr, SOC_DEVICE_TYPE_BUFFER_SIZE);
			gPESoCDeviceType = gPESoCDeviceTypeBuffer;

			DTGetProperty(entryP, "ranges", (void **)&ranges_prop, &prop_size);
			gPESoCBasePhys = *(ranges_prop + 1);
		}
		return gPESoCBasePhys;
	}
	return 0;
}