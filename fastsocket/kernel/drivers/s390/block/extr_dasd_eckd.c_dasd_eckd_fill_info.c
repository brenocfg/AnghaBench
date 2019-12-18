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
struct dasd_information2_t {int label_block; int FBA_layout; int characteristics_size; int confdata_size; int /*<<< orphan*/  configuration_data; int /*<<< orphan*/  characteristics; int /*<<< orphan*/  format; } ;
struct dasd_eckd_private {int /*<<< orphan*/ * conf_data; scalar_t__ conf_len; int /*<<< orphan*/  rdc_data; scalar_t__ uses_cdl; } ;
struct dasd_eckd_characteristics {int dummy; } ;
struct dasd_device {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_FORMAT_CDL ; 
 int /*<<< orphan*/  DASD_FORMAT_LDL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int min (unsigned long,int) ; 

__attribute__((used)) static int
dasd_eckd_fill_info(struct dasd_device * device,
		    struct dasd_information2_t * info)
{
	struct dasd_eckd_private *private;

	private = (struct dasd_eckd_private *) device->private;
	info->label_block = 2;
	info->FBA_layout = private->uses_cdl ? 0 : 1;
	info->format = private->uses_cdl ? DASD_FORMAT_CDL : DASD_FORMAT_LDL;
	info->characteristics_size = sizeof(struct dasd_eckd_characteristics);
	memcpy(info->characteristics, &private->rdc_data,
	       sizeof(struct dasd_eckd_characteristics));
	info->confdata_size = min((unsigned long)private->conf_len,
				  sizeof(info->configuration_data));
	memcpy(info->configuration_data, private->conf_data,
	       info->confdata_size);
	return 0;
}