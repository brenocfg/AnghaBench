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
typedef  int u8 ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
#define  TPACPI_FAN_RD_ACPI_GFAN 129 
#define  TPACPI_FAN_RD_TPEC 128 
 int /*<<< orphan*/  acpi_ec_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fan_quirk1_handle (int*) ; 
 int fan_status_access_mode ; 
 int /*<<< orphan*/  fan_status_offset ; 
 int /*<<< orphan*/  gfan_handle ; 
 int /*<<< orphan*/  likely (int*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int fan_get_status(u8 *status)
{
	u8 s;

	/* TODO:
	 * Add TPACPI_FAN_RD_ACPI_FANS ? */

	switch (fan_status_access_mode) {
	case TPACPI_FAN_RD_ACPI_GFAN:
		/* 570, 600e/x, 770e, 770x */

		if (unlikely(!acpi_evalf(gfan_handle, &s, NULL, "d")))
			return -EIO;

		if (likely(status))
			*status = s & 0x07;

		break;

	case TPACPI_FAN_RD_TPEC:
		/* all except 570, 600e/x, 770e, 770x */
		if (unlikely(!acpi_ec_read(fan_status_offset, &s)))
			return -EIO;

		if (likely(status)) {
			*status = s;
			fan_quirk1_handle(status);
		}

		break;

	default:
		return -ENXIO;
	}

	return 0;
}