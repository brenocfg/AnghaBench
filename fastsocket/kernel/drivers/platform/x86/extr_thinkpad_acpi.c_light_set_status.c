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
struct TYPE_2__ {scalar_t__ light; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int TP_CMOS_THINKLIGHT_OFF ; 
 int TP_CMOS_THINKLIGHT_ON ; 
 int acpi_evalf (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ cmos_handle ; 
 scalar_t__ lght_handle ; 
 TYPE_1__ tp_features ; 

__attribute__((used)) static int light_set_status(int status)
{
	int rc;

	if (tp_features.light) {
		if (cmos_handle) {
			rc = acpi_evalf(cmos_handle, NULL, NULL, "vd",
					(status)?
						TP_CMOS_THINKLIGHT_ON :
						TP_CMOS_THINKLIGHT_OFF);
		} else {
			rc = acpi_evalf(lght_handle, NULL, NULL, "vd",
					(status)? 1 : 0);
		}
		return (rc)? 0 : -EIO;
	}

	return -ENXIO;
}