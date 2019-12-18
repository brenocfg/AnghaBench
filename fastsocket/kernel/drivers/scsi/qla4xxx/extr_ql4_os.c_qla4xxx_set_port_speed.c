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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int addl_fw_state; } ;
struct iscsi_cls_host {int /*<<< orphan*/  port_speed; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
#define  FW_ADDSTATE_LINK_SPEED_100MBPS 131 
#define  FW_ADDSTATE_LINK_SPEED_10GBPS 130 
#define  FW_ADDSTATE_LINK_SPEED_10MBPS 129 
#define  FW_ADDSTATE_LINK_SPEED_1GBPS 128 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_100MBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_10GBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_10MBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_1GBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  qla4xxx_get_firmware_state (struct scsi_qla_host*) ; 
 struct scsi_qla_host* to_qla_host (struct Scsi_Host*) ; 

__attribute__((used)) static void qla4xxx_set_port_speed(struct Scsi_Host *shost)
{
	struct scsi_qla_host *ha = to_qla_host(shost);
	struct iscsi_cls_host *ihost = shost->shost_data;
	uint32_t speed = ISCSI_PORT_SPEED_UNKNOWN;

	qla4xxx_get_firmware_state(ha);

	switch (ha->addl_fw_state & 0x0F00) {
	case FW_ADDSTATE_LINK_SPEED_10MBPS:
		speed = ISCSI_PORT_SPEED_10MBPS;
		break;
	case FW_ADDSTATE_LINK_SPEED_100MBPS:
		speed = ISCSI_PORT_SPEED_100MBPS;
		break;
	case FW_ADDSTATE_LINK_SPEED_1GBPS:
		speed = ISCSI_PORT_SPEED_1GBPS;
		break;
	case FW_ADDSTATE_LINK_SPEED_10GBPS:
		speed = ISCSI_PORT_SPEED_10GBPS;
		break;
	}
	ihost->port_speed = speed;
}