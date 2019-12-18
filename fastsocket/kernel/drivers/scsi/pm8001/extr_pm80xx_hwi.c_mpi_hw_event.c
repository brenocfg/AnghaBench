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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sas_ha_struct {int /*<<< orphan*/  (* notify_port_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* notify_phy_event ) (struct asd_sas_phy*,int /*<<< orphan*/ ) ;struct asd_sas_phy** sas_phy; } ;
struct asd_sas_phy {int sas_prim; int /*<<< orphan*/  sas_prim_lock; } ;
struct pm8001_phy {int /*<<< orphan*/  phy_attached; struct asd_sas_phy sas_phy; int /*<<< orphan*/  phy_state; } ;
struct pm8001_hba_info {struct pm8001_phy* phy; struct sas_ha_struct* sas; } ;
struct hw_event_resp {int /*<<< orphan*/  phyid_npip_portstate; int /*<<< orphan*/  lr_status_evt_portid; } ;

/* Variables and functions */
#define  EVENT_BROADCAST_ASYNCH_EVENT 150 
#define  HW_EVENT_BROADCAST_CHANGE 149 
#define  HW_EVENT_BROADCAST_EXP 148 
#define  HW_EVENT_BROADCAST_SES 147 
#define  HW_EVENT_HARD_RESET_RECEIVED 146 
#define  HW_EVENT_ID_FRAME_TIMEOUT 145 
#define  HW_EVENT_INBOUND_CRC_ERROR 144 
#define  HW_EVENT_LINK_ERR_CODE_VIOLATION 143 
#define  HW_EVENT_LINK_ERR_DISPARITY_ERROR 142 
#define  HW_EVENT_LINK_ERR_INVALID_DWORD 141 
#define  HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH 140 
#define  HW_EVENT_LINK_ERR_PHY_RESET_FAILED 139 
#define  HW_EVENT_MALFUNCTION 138 
#define  HW_EVENT_PHY_DOWN 137 
#define  HW_EVENT_PHY_ERROR 136 
#define  HW_EVENT_PORT_INVALID 135 
#define  HW_EVENT_PORT_RECOVER 134 
#define  HW_EVENT_PORT_RECOVERY_TIMER_TMO 133 
#define  HW_EVENT_PORT_RESET_COMPLETE 132 
#define  HW_EVENT_PORT_RESET_TIMER_TMO 131 
#define  HW_EVENT_SAS_PHY_UP 130 
#define  HW_EVENT_SATA_PHY_UP 129 
#define  HW_EVENT_SATA_SPINUP_HOLD 128 
 int /*<<< orphan*/  PHYE_LOSS_OF_SIGNAL ; 
 int /*<<< orphan*/  PHYE_OOB_ERROR ; 
 int /*<<< orphan*/  PHYE_SPINUP_HOLD ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTE_BROADCAST_RCVD ; 
 int /*<<< orphan*/  PORTE_HARD_RESET ; 
 int /*<<< orphan*/  PORTE_LINK_RESET_ERR ; 
 int /*<<< orphan*/  hw_event_phy_down (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  hw_event_sas_phy_up (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  hw_event_sata_phy_up (struct pm8001_hba_info*,void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  pm80xx_hw_event_ack_req (struct pm8001_hba_info*,int /*<<< orphan*/ ,int const,size_t,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_phy_disconnected (struct asd_sas_phy*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpi_hw_event(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	unsigned long flags;
	struct hw_event_resp *pPayload =
		(struct hw_event_resp *)(piomb + 4);
	u32 lr_status_evt_portid =
		le32_to_cpu(pPayload->lr_status_evt_portid);
	u32 phyid_npip_portstate = le32_to_cpu(pPayload->phyid_npip_portstate);
	u8 port_id = (u8)(lr_status_evt_portid & 0x000000FF);
	u8 phy_id =
		(u8)((phyid_npip_portstate & 0xFF0000) >> 16);
	u16 eventType =
		(u16)((lr_status_evt_portid & 0x00FFFF00) >> 8);
	u8 status =
		(u8)((lr_status_evt_portid & 0x0F000000) >> 24);

	struct sas_ha_struct *sas_ha = pm8001_ha->sas;
	struct pm8001_phy *phy = &pm8001_ha->phy[phy_id];
	struct asd_sas_phy *sas_phy = sas_ha->sas_phy[phy_id];
	PM8001_MSG_DBG(pm8001_ha,
		pm8001_printk("portid:%d phyid:%d event:0x%x status:0x%x\n",
				port_id, phy_id, eventType, status));

	switch (eventType) {

	case HW_EVENT_SAS_PHY_UP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PHY_START_STATUS\n"));
		hw_event_sas_phy_up(pm8001_ha, piomb);
		break;
	case HW_EVENT_SATA_PHY_UP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_SATA_PHY_UP\n"));
		hw_event_sata_phy_up(pm8001_ha, piomb);
		break;
	case HW_EVENT_SATA_SPINUP_HOLD:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_SATA_SPINUP_HOLD\n"));
		sas_ha->notify_phy_event(&phy->sas_phy, PHYE_SPINUP_HOLD);
		break;
	case HW_EVENT_PHY_DOWN:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PHY_DOWN\n"));
		sas_ha->notify_phy_event(&phy->sas_phy, PHYE_LOSS_OF_SIGNAL);
		phy->phy_attached = 0;
		phy->phy_state = 0;
		hw_event_phy_down(pm8001_ha, piomb);
		break;
	case HW_EVENT_PORT_INVALID:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PORT_INVALID\n"));
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	/* the broadcast change primitive received, tell the LIBSAS this event
	to revalidate the sas domain*/
	case HW_EVENT_BROADCAST_CHANGE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_BROADCAST_CHANGE\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0, HW_EVENT_BROADCAST_CHANGE,
			port_id, phy_id, 1, 0);
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_CHANGE;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_ha->notify_port_event(sas_phy, PORTE_BROADCAST_RCVD);
		break;
	case HW_EVENT_PHY_ERROR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PHY_ERROR\n"));
		sas_phy_disconnected(&phy->sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_phy_event(&phy->sas_phy, PHYE_OOB_ERROR);
		break;
	case HW_EVENT_BROADCAST_EXP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_BROADCAST_EXP\n"));
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_EXP;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_ha->notify_port_event(sas_phy, PORTE_BROADCAST_RCVD);
		break;
	case HW_EVENT_LINK_ERR_INVALID_DWORD:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_LINK_ERR_INVALID_DWORD\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_INVALID_DWORD, port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_LINK_ERR_DISPARITY_ERROR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_LINK_ERR_DISPARITY_ERROR\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_DISPARITY_ERROR,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_LINK_ERR_CODE_VIOLATION:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_LINK_ERR_CODE_VIOLATION\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_CODE_VIOLATION,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH:
		PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_LOSS_OF_DWORD_SYNCH,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_MALFUNCTION:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_MALFUNCTION\n"));
		break;
	case HW_EVENT_BROADCAST_SES:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_BROADCAST_SES\n"));
		spin_lock_irqsave(&sas_phy->sas_prim_lock, flags);
		sas_phy->sas_prim = HW_EVENT_BROADCAST_SES;
		spin_unlock_irqrestore(&sas_phy->sas_prim_lock, flags);
		sas_ha->notify_port_event(sas_phy, PORTE_BROADCAST_RCVD);
		break;
	case HW_EVENT_INBOUND_CRC_ERROR:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_INBOUND_CRC_ERROR\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_INBOUND_CRC_ERROR,
			port_id, phy_id, 0, 0);
		break;
	case HW_EVENT_HARD_RESET_RECEIVED:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_HARD_RESET_RECEIVED\n"));
		sas_ha->notify_port_event(sas_phy, PORTE_HARD_RESET);
		break;
	case HW_EVENT_ID_FRAME_TIMEOUT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_ID_FRAME_TIMEOUT\n"));
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_LINK_ERR_PHY_RESET_FAILED:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_LINK_ERR_PHY_RESET_FAILED\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_LINK_ERR_PHY_RESET_FAILED,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_PORT_RESET_TIMER_TMO:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PORT_RESET_TIMER_TMO\n"));
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_PORT_RECOVERY_TIMER_TMO:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PORT_RECOVERY_TIMER_TMO\n"));
		pm80xx_hw_event_ack_req(pm8001_ha, 0,
			HW_EVENT_PORT_RECOVERY_TIMER_TMO,
			port_id, phy_id, 0, 0);
		sas_phy_disconnected(sas_phy);
		phy->phy_attached = 0;
		sas_ha->notify_port_event(sas_phy, PORTE_LINK_RESET_ERR);
		break;
	case HW_EVENT_PORT_RECOVER:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PORT_RECOVER\n"));
		break;
	case HW_EVENT_PORT_RESET_COMPLETE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("HW_EVENT_PORT_RESET_COMPLETE\n"));
		break;
	case EVENT_BROADCAST_ASYNCH_EVENT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("EVENT_BROADCAST_ASYNCH_EVENT\n"));
		break;
	default:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("Unknown event type 0x%x\n", eventType));
		break;
	}
	return 0;
}