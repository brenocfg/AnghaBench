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
struct pcc_acpi {int* sinf; } ;
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SINF_AC_CUR_BRIGHT ; 
 size_t SINF_AC_MAX_BRIGHT ; 
 size_t SINF_AC_MIN_BRIGHT ; 
 int /*<<< orphan*/  SINF_DC_CUR_BRIGHT ; 
 size_t SINF_DC_MIN_BRIGHT ; 
 int /*<<< orphan*/  acpi_pcc_retrieve_biosdata (struct pcc_acpi*,int*) ; 
 int acpi_pcc_write_sset (struct pcc_acpi*,int /*<<< orphan*/ ,int) ; 
 struct pcc_acpi* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int bl_set_status(struct backlight_device *bd)
{
	struct pcc_acpi *pcc = bl_get_data(bd);
	int bright = bd->props.brightness;
	int rc;

	if (!acpi_pcc_retrieve_biosdata(pcc, pcc->sinf))
		return -EIO;

	if (bright < pcc->sinf[SINF_AC_MIN_BRIGHT])
		bright = pcc->sinf[SINF_AC_MIN_BRIGHT];

	if (bright < pcc->sinf[SINF_DC_MIN_BRIGHT])
		bright = pcc->sinf[SINF_DC_MIN_BRIGHT];

	if (bright < pcc->sinf[SINF_AC_MIN_BRIGHT] ||
	    bright > pcc->sinf[SINF_AC_MAX_BRIGHT])
		return -EINVAL;

	rc = acpi_pcc_write_sset(pcc, SINF_AC_CUR_BRIGHT, bright);
	if (rc < 0)
		return rc;

	return acpi_pcc_write_sset(pcc, SINF_DC_CUR_BRIGHT, bright);
}