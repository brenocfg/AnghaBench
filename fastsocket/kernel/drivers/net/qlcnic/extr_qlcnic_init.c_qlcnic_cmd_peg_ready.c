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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
#define  PHAN_INITIALIZE_ACK 130 
#define  PHAN_INITIALIZE_COMPLETE 129 
#define  PHAN_INITIALIZE_FAILED 128 
 int /*<<< orphan*/  QLCNIC_CMDPEG_CHECK_DELAY ; 
 int QLCNIC_CMDPEG_CHECK_RETRY_COUNT ; 
 int /*<<< orphan*/  QLCNIC_CMDPEG_STATE ; 
 int QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_cmd_peg_ready(struct qlcnic_adapter *adapter)
{
	u32 val;
	int retries = QLCNIC_CMDPEG_CHECK_RETRY_COUNT;

	do {
		val = QLC_SHARED_REG_RD32(adapter, QLCNIC_CMDPEG_STATE);

		switch (val) {
		case PHAN_INITIALIZE_COMPLETE:
		case PHAN_INITIALIZE_ACK:
			return 0;
		case PHAN_INITIALIZE_FAILED:
			goto out_err;
		default:
			break;
		}

		msleep(QLCNIC_CMDPEG_CHECK_DELAY);

	} while (--retries);

	QLC_SHARED_REG_WR32(adapter, QLCNIC_CMDPEG_STATE,
			    PHAN_INITIALIZE_FAILED);

out_err:
	dev_err(&adapter->pdev->dev, "Command Peg initialization not "
		      "complete, state: 0x%x.\n", val);
	return -EIO;
}