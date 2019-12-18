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
struct iscsi_cls_host {int port_speed; } ;
struct beiscsi_hba {int dummy; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_ntwk_link_status_resp {int mac_speed; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
#define  BE2ISCSI_LINK_SPEED_100MBPS 131 
#define  BE2ISCSI_LINK_SPEED_10GBPS 130 
#define  BE2ISCSI_LINK_SPEED_10MBPS 129 
#define  BE2ISCSI_LINK_SPEED_1GBPS 128 
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_MBOX ; 
 int EBUSY ; 
 int ISCSI_PORT_SPEED_10GBPS ; 
 int ISCSI_PORT_SPEED_10MBPS ; 
 int ISCSI_PORT_SPEED_1GBPS ; 
 int ISCSI_PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 unsigned int be_cmd_get_port_speed (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int beiscsi_mccq_compl (struct beiscsi_hba*,unsigned int,struct be_mcc_wrb**,int /*<<< orphan*/ *) ; 
 struct be_cmd_ntwk_link_status_resp* embedded_payload (struct be_mcc_wrb*) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 

__attribute__((used)) static int beiscsi_get_port_speed(struct Scsi_Host *shost)
{
	int rc;
	unsigned int tag;
	struct be_mcc_wrb *wrb;
	struct be_cmd_ntwk_link_status_resp *resp;
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	struct iscsi_cls_host *ihost = shost->shost_data;

	tag = be_cmd_get_port_speed(phba);
	if (!tag) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Getting Port Speed Failed\n");

		 return -EBUSY;
	}
	rc = beiscsi_mccq_compl(phba, tag, &wrb, NULL);
	if (rc) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BS_%d : Port Speed MBX Failed\n");
		return rc;
	}
	resp = embedded_payload(wrb);

	switch (resp->mac_speed) {
	case BE2ISCSI_LINK_SPEED_10MBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_10MBPS;
		break;
	case BE2ISCSI_LINK_SPEED_100MBPS:
		ihost->port_speed = BE2ISCSI_LINK_SPEED_100MBPS;
		break;
	case BE2ISCSI_LINK_SPEED_1GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_1GBPS;
		break;
	case BE2ISCSI_LINK_SPEED_10GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_10GBPS;
		break;
	default:
		ihost->port_speed = ISCSI_PORT_SPEED_UNKNOWN;
	}
	return 0;
}