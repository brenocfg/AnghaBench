#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct TYPE_6__ {int /*<<< orphan*/  event_trigger; int /*<<< orphan*/  flow_trigger; } ;
struct iwl_tlv_calib_data {TYPE_3__ calib; int /*<<< orphan*/  ucode_type; } ;
struct TYPE_5__ {TYPE_1__* default_calib; } ;
struct iwl_drv {TYPE_2__ fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_trigger; int /*<<< orphan*/  flow_trigger; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_drv*,char*,size_t) ; 
 size_t IWL_UCODE_TYPE_MAX ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_set_default_calib(struct iwl_drv *drv, const u8 *data)
{
	struct iwl_tlv_calib_data *def_calib =
					(struct iwl_tlv_calib_data *)data;
	u32 ucode_type = le32_to_cpu(def_calib->ucode_type);
	if (ucode_type >= IWL_UCODE_TYPE_MAX) {
		IWL_ERR(drv, "Wrong ucode_type %u for default calibration.\n",
			ucode_type);
		return -EINVAL;
	}
	drv->fw.default_calib[ucode_type].flow_trigger =
		def_calib->calib.flow_trigger;
	drv->fw.default_calib[ucode_type].event_trigger =
		def_calib->calib.event_trigger;

	return 0;
}