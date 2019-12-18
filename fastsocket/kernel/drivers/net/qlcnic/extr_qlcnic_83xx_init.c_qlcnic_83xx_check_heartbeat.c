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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {scalar_t__ heartbeat; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_FWERROR_CODE (scalar_t__) ; 
 int QLCNIC_HEARTBEAT_CHECK_RETRY_COUNT ; 
 int /*<<< orphan*/  QLCNIC_HEARTBEAT_PERIOD_MSECS ; 
 int /*<<< orphan*/  QLCNIC_PEG_ALIVE_COUNTER ; 
 int /*<<< orphan*/  QLCNIC_PEG_HALT_STATUS1 ; 
 int /*<<< orphan*/  QLCNIC_PEG_HALT_STATUS2 ; 
 int QLCNIC_RCODE_SUCCESS ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_CRB_PEG_NET_0 ; 
 int /*<<< orphan*/  QLC_83XX_CRB_PEG_NET_1 ; 
 int /*<<< orphan*/  QLC_83XX_CRB_PEG_NET_2 ; 
 int /*<<< orphan*/  QLC_83XX_CRB_PEG_NET_3 ; 
 int /*<<< orphan*/  QLC_83XX_CRB_PEG_NET_4 ; 
 void* QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_disable_pause_frames (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_take_eport_out_of_reset (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_83xx_check_heartbeat(struct qlcnic_adapter *p_dev)
{
	u32 heartbeat, peg_status;
	int retries, ret = -EIO;

	retries = QLCNIC_HEARTBEAT_CHECK_RETRY_COUNT;
	p_dev->heartbeat = QLC_SHARED_REG_RD32(p_dev,
					       QLCNIC_PEG_ALIVE_COUNTER);

	do {
		msleep(QLCNIC_HEARTBEAT_PERIOD_MSECS);
		heartbeat = QLC_SHARED_REG_RD32(p_dev,
						QLCNIC_PEG_ALIVE_COUNTER);
		if (heartbeat != p_dev->heartbeat) {
			ret = QLCNIC_RCODE_SUCCESS;
			break;
		}
	} while (--retries);

	if (ret) {
		dev_err(&p_dev->pdev->dev, "firmware hang detected\n");
		qlcnic_83xx_take_eport_out_of_reset(p_dev);
		qlcnic_83xx_disable_pause_frames(p_dev);
		peg_status = QLC_SHARED_REG_RD32(p_dev,
						 QLCNIC_PEG_HALT_STATUS1);
		dev_info(&p_dev->pdev->dev, "Dumping HW/FW registers\n"
			 "PEG_HALT_STATUS1: 0x%x, PEG_HALT_STATUS2: 0x%x,\n"
			 "PEG_NET_0_PC: 0x%x, PEG_NET_1_PC: 0x%x,\n"
			 "PEG_NET_2_PC: 0x%x, PEG_NET_3_PC: 0x%x,\n"
			 "PEG_NET_4_PC: 0x%x\n", peg_status,
			 QLC_SHARED_REG_RD32(p_dev, QLCNIC_PEG_HALT_STATUS2),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_0),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_1),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_2),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_3),
			 QLCRD32(p_dev, QLC_83XX_CRB_PEG_NET_4));

		if (QLCNIC_FWERROR_CODE(peg_status) == 0x67)
			dev_err(&p_dev->pdev->dev,
				"Device is being reset err code 0x00006700.\n");
	}

	return ret;
}