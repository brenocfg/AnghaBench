#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int bios_hardcoded_edid_size; struct edid* bios_hardcoded_edid; } ;
struct radeon_device {unsigned char* bios; TYPE_1__ mode_info; int /*<<< orphan*/  ddev; } ;
struct edid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMBIOS_HARDCODED_EDID_TABLE ; 
 unsigned char EDID_LENGTH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int combios_get_table_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_edid_is_valid (struct edid*) ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 
 struct edid* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

bool radeon_combios_check_hardcoded_edid(struct radeon_device *rdev)
{
	int edid_info, size;
	struct edid *edid;
	unsigned char *raw;
	edid_info = combios_get_table_offset(rdev->ddev, COMBIOS_HARDCODED_EDID_TABLE);
	if (!edid_info)
		return false;

	raw = rdev->bios + edid_info;
	size = EDID_LENGTH * (raw[0x7e] + 1);
	edid = kmalloc(size, GFP_KERNEL);
	if (edid == NULL)
		return false;

	memcpy((unsigned char *)edid, raw, size);

	if (!drm_edid_is_valid(edid)) {
		kfree(edid);
		return false;
	}

	rdev->mode_info.bios_hardcoded_edid = edid;
	rdev->mode_info.bios_hardcoded_edid_size = size;
	return true;
}