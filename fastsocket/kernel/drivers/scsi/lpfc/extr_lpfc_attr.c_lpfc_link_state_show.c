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
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  port_state; struct lpfc_hba* phba; } ;
struct TYPE_2__ {int sli_flag; } ;
struct lpfc_hba {int link_state; int hba_flag; int /*<<< orphan*/  fc_topology; TYPE_1__ sli; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int FC_FABRIC ; 
 int FC_PUBLIC_LOOP ; 
 int LINK_DISABLED ; 
#define  LPFC_BUILD_DISC_LIST 147 
#define  LPFC_CLEAR_LA 146 
#define  LPFC_DISC_AUTH 145 
#define  LPFC_FABRIC_CFG_LINK 144 
#define  LPFC_FDISC 143 
#define  LPFC_FLOGI 142 
#define  LPFC_HBA_ERROR 141 
#define  LPFC_HBA_READY 140 
#define  LPFC_INIT_MBX_CMDS 139 
#define  LPFC_INIT_START 138 
#define  LPFC_LINK_DOWN 137 
#define  LPFC_LINK_UNKNOWN 136 
#define  LPFC_LINK_UP 135 
#define  LPFC_LOCAL_CFG_LINK 134 
 int LPFC_MENLO_MAINT ; 
#define  LPFC_NS_QRY 133 
#define  LPFC_NS_REG 132 
 int /*<<< orphan*/  LPFC_TOPOLOGY_LOOP ; 
#define  LPFC_VPORT_FAILED 131 
#define  LPFC_VPORT_READY 130 
#define  LPFC_VPORT_UNKNOWN 129 
#define  LPFC_WARM_START 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
lpfc_link_state_show(struct device *dev, struct device_attribute *attr,
		     char *buf)
{
	struct Scsi_Host  *shost = class_to_shost(dev);
	struct lpfc_vport *vport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = vport->phba;
	int  len = 0;

	switch (phba->link_state) {
	case LPFC_LINK_UNKNOWN:
	case LPFC_WARM_START:
	case LPFC_INIT_START:
	case LPFC_INIT_MBX_CMDS:
	case LPFC_LINK_DOWN:
	case LPFC_HBA_ERROR:
		if (phba->hba_flag & LINK_DISABLED)
			len += snprintf(buf + len, PAGE_SIZE-len,
				"Link Down - User disabled\n");
		else
			len += snprintf(buf + len, PAGE_SIZE-len,
				"Link Down\n");
		break;
	case LPFC_LINK_UP:
	case LPFC_CLEAR_LA:
	case LPFC_HBA_READY:
		len += snprintf(buf + len, PAGE_SIZE-len, "Link Up - ");

		switch (vport->port_state) {
		case LPFC_LOCAL_CFG_LINK:
			len += snprintf(buf + len, PAGE_SIZE-len,
					"Configuring Link\n");
			break;
		case LPFC_FDISC:
		case LPFC_FLOGI:
		case LPFC_FABRIC_CFG_LINK:
		case LPFC_NS_REG:
		case LPFC_NS_QRY:
		case LPFC_BUILD_DISC_LIST:
		case LPFC_DISC_AUTH:
			len += snprintf(buf + len, PAGE_SIZE - len,
					"Discovery\n");
			break;
		case LPFC_VPORT_READY:
			len += snprintf(buf + len, PAGE_SIZE - len, "Ready\n");
			break;

		case LPFC_VPORT_FAILED:
			len += snprintf(buf + len, PAGE_SIZE - len, "Failed\n");
			break;

		case LPFC_VPORT_UNKNOWN:
			len += snprintf(buf + len, PAGE_SIZE - len,
					"Unknown\n");
			break;
		}
		if (phba->sli.sli_flag & LPFC_MENLO_MAINT)
			len += snprintf(buf + len, PAGE_SIZE-len,
					"   Menlo Maint Mode\n");
		else if (phba->fc_topology == LPFC_TOPOLOGY_LOOP) {
			if (vport->fc_flag & FC_PUBLIC_LOOP)
				len += snprintf(buf + len, PAGE_SIZE-len,
						"   Public Loop\n");
			else
				len += snprintf(buf + len, PAGE_SIZE-len,
						"   Private Loop\n");
		} else {
			if (vport->fc_flag & FC_FABRIC)
				len += snprintf(buf + len, PAGE_SIZE-len,
						"   Fabric\n");
			else
				len += snprintf(buf + len, PAGE_SIZE-len,
						"   Point-2-Point\n");
		}
	}

	return len;
}