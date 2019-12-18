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
typedef  int /*<<< orphan*/  tmpi ;
typedef  int s8 ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOSYS ; 
#define  TPACPI_THERMAL_ACPI_TMP07 132 
#define  TPACPI_THERMAL_ACPI_UPDT 131 
#define  TPACPI_THERMAL_NONE 130 
#define  TPACPI_THERMAL_TPEC_16 129 
#define  TPACPI_THERMAL_TPEC_8 128 
 int TP_EC_THERMAL_TMP0 ; 
 int TP_EC_THERMAL_TMP8 ; 
 int TP_EC_THERMAL_TMP_NA ; 
 int /*<<< orphan*/  acpi_ec_read (int,int*) ; 
 int /*<<< orphan*/  acpi_evalf (int /*<<< orphan*/ ,int*,char*,char*) ; 
 int /*<<< orphan*/  ec_handle ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int thermal_read_mode ; 

__attribute__((used)) static int thermal_get_sensor(int idx, s32 *value)
{
	int t;
	s8 tmp;
	char tmpi[5];

	t = TP_EC_THERMAL_TMP0;

	switch (thermal_read_mode) {
#if TPACPI_MAX_THERMAL_SENSORS >= 16
	case TPACPI_THERMAL_TPEC_16:
		if (idx >= 8 && idx <= 15) {
			t = TP_EC_THERMAL_TMP8;
			idx -= 8;
		}
		/* fallthrough */
#endif
	case TPACPI_THERMAL_TPEC_8:
		if (idx <= 7) {
			if (!acpi_ec_read(t + idx, &tmp))
				return -EIO;
			*value = tmp * 1000;
			return 0;
		}
		break;

	case TPACPI_THERMAL_ACPI_UPDT:
		if (idx <= 7) {
			snprintf(tmpi, sizeof(tmpi), "TMP%c", '0' + idx);
			if (!acpi_evalf(ec_handle, NULL, "UPDT", "v"))
				return -EIO;
			if (!acpi_evalf(ec_handle, &t, tmpi, "d"))
				return -EIO;
			*value = (t - 2732) * 100;
			return 0;
		}
		break;

	case TPACPI_THERMAL_ACPI_TMP07:
		if (idx <= 7) {
			snprintf(tmpi, sizeof(tmpi), "TMP%c", '0' + idx);
			if (!acpi_evalf(ec_handle, &t, tmpi, "d"))
				return -EIO;
			if (t > 127 || t < -127)
				t = TP_EC_THERMAL_TMP_NA;
			*value = t * 1000;
			return 0;
		}
		break;

	case TPACPI_THERMAL_NONE:
	default:
		return -ENOSYS;
	}

	return -EINVAL;
}