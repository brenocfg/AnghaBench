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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  fan_ctrl_status_undef; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int EPERM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  TPACPI_DBG_FAN ; 
#define  TPACPI_FAN_WR_ACPI_FANS 130 
#define  TPACPI_FAN_WR_ACPI_SFAN 129 
#define  TPACPI_FAN_WR_TPEC 128 
 int TP_EC_FAN_AUTO ; 
 int /*<<< orphan*/  acpi_ec_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int fan_control_access_mode ; 
 int /*<<< orphan*/  fan_control_allowed ; 
 int fan_get_status (int*) ; 
 int /*<<< orphan*/  fan_mutex ; 
 int /*<<< orphan*/  fan_status_offset ; 
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfan_handle ; 
 TYPE_1__ tp_features ; 
 int /*<<< orphan*/  vdbg_printk (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int fan_set_enable(void)
{
	u8 s;
	int rc;

	if (!fan_control_allowed)
		return -EPERM;

	if (mutex_lock_killable(&fan_mutex))
		return -ERESTARTSYS;

	switch (fan_control_access_mode) {
	case TPACPI_FAN_WR_ACPI_FANS:
	case TPACPI_FAN_WR_TPEC:
		rc = fan_get_status(&s);
		if (rc < 0)
			break;

		/* Don't go out of emergency fan mode */
		if (s != 7) {
			s &= 0x07;
			s |= TP_EC_FAN_AUTO | 4; /* min fan speed 4 */
		}

		if (!acpi_ec_write(fan_status_offset, s))
			rc = -EIO;
		else {
			tp_features.fan_ctrl_status_undef = 0;
			rc = 0;
		}
		break;

	case TPACPI_FAN_WR_ACPI_SFAN:
		rc = fan_get_status(&s);
		if (rc < 0)
			break;

		s &= 0x07;

		/* Set fan to at least level 4 */
		s |= 4;

		if (!acpi_evalf(sfan_handle, NULL, NULL, "vd", s))
			rc = -EIO;
		else
			rc = 0;
		break;

	default:
		rc = -ENXIO;
	}

	mutex_unlock(&fan_mutex);

	if (!rc)
		vdbg_printk(TPACPI_DBG_FAN,
			"fan control: set fan control register to 0x%02x\n",
			s);
	return rc;
}