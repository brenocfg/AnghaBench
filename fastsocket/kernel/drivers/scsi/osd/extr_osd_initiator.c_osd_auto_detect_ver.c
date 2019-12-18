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
struct osd_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_DEBUG (char*) ; 
 int /*<<< orphan*/  OSD_VER1 ; 
 int _osd_print_system_info (struct osd_dev*,void*) ; 
 int /*<<< orphan*/  osd_dev_set_ver (struct osd_dev*,int /*<<< orphan*/ ) ; 

int osd_auto_detect_ver(struct osd_dev *od, void *caps)
{
	int ret;

	/* Auto-detect the osd version */
	ret = _osd_print_system_info(od, caps);
	if (ret) {
		osd_dev_set_ver(od, OSD_VER1);
		OSD_DEBUG("converting to OSD1\n");
		ret = _osd_print_system_info(od, caps);
	}

	return ret;
}