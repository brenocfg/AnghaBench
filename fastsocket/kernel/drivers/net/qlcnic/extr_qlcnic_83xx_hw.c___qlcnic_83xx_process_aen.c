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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_hardware_context {int* mbox_aen; } ;
struct qlcnic_adapter {TYPE_1__* pdev; int /*<<< orphan*/  idc_aen_work; int /*<<< orphan*/  qlcnic_wq; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_CLR_OWNER ; 
 int /*<<< orphan*/  QLCNIC_FW_MBX_CTRL ; 
#define  QLCNIC_MBX_BC_EVENT 134 
#define  QLCNIC_MBX_COMP_EVENT 133 
 int /*<<< orphan*/  QLCNIC_MBX_FW (struct qlcnic_hardware_context*,int) ; 
#define  QLCNIC_MBX_LINK_EVENT 132 
#define  QLCNIC_MBX_REQUEST_EVENT 131 
 int QLCNIC_MBX_RSP (int /*<<< orphan*/ ) ; 
#define  QLCNIC_MBX_SFP_INSERT_EVENT 130 
#define  QLCNIC_MBX_SFP_REMOVE_EVENT 129 
#define  QLCNIC_MBX_TIME_EXTEND_EVENT 128 
 int /*<<< orphan*/  QLCWRX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int QLC_83XX_MBX_AEN_CNT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_handle_idc_comp_aen (struct qlcnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_83xx_handle_link_aen (struct qlcnic_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_handle_bc_event (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

void __qlcnic_83xx_process_aen(struct qlcnic_adapter *adapter)
{
	u32 event[QLC_83XX_MBX_AEN_CNT];
	int i;
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	for (i = 0; i < QLC_83XX_MBX_AEN_CNT; i++)
		event[i] = readl(QLCNIC_MBX_FW(ahw, i));

	switch (QLCNIC_MBX_RSP(event[0])) {

	case QLCNIC_MBX_LINK_EVENT:
		qlcnic_83xx_handle_link_aen(adapter, event);
		break;
	case QLCNIC_MBX_COMP_EVENT:
		qlcnic_83xx_handle_idc_comp_aen(adapter, event);
		break;
	case QLCNIC_MBX_REQUEST_EVENT:
		for (i = 0; i < QLC_83XX_MBX_AEN_CNT; i++)
			adapter->ahw->mbox_aen[i] = QLCNIC_MBX_RSP(event[i]);
		queue_delayed_work(adapter->qlcnic_wq,
				   &adapter->idc_aen_work, 0);
		break;
	case QLCNIC_MBX_TIME_EXTEND_EVENT:
		break;
	case QLCNIC_MBX_BC_EVENT:
		qlcnic_sriov_handle_bc_event(adapter, event[1]);
		break;
	case QLCNIC_MBX_SFP_INSERT_EVENT:
		dev_info(&adapter->pdev->dev, "SFP+ Insert AEN:0x%x.\n",
			 QLCNIC_MBX_RSP(event[0]));
		break;
	case QLCNIC_MBX_SFP_REMOVE_EVENT:
		dev_info(&adapter->pdev->dev, "SFP Removed AEN:0x%x.\n",
			 QLCNIC_MBX_RSP(event[0]));
		break;
	default:
		dev_dbg(&adapter->pdev->dev, "Unsupported AEN:0x%x.\n",
			QLCNIC_MBX_RSP(event[0]));
		break;
	}

	QLCWRX(ahw, QLCNIC_FW_MBX_CTRL, QLCNIC_CLR_OWNER);
}