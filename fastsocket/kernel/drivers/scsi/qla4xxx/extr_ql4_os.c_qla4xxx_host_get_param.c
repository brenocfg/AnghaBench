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
struct TYPE_2__ {char ip_address; } ;
struct scsi_qla_host {char* name_string; TYPE_1__ ip_config; int /*<<< orphan*/  my_mac; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum iscsi_host_param { ____Placeholder_iscsi_host_param } iscsi_host_param ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_HOST_PARAM_HWADDRESS 132 
#define  ISCSI_HOST_PARAM_INITIATOR_NAME 131 
#define  ISCSI_HOST_PARAM_IPADDRESS 130 
#define  ISCSI_HOST_PARAM_PORT_SPEED 129 
#define  ISCSI_HOST_PARAM_PORT_STATE 128 
 int /*<<< orphan*/  MAC_ADDR_LEN ; 
 char* iscsi_get_port_speed_name (struct Scsi_Host*) ; 
 char* iscsi_get_port_state_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  qla4xxx_set_port_speed (struct Scsi_Host*) ; 
 int /*<<< orphan*/  qla4xxx_set_port_state (struct Scsi_Host*) ; 
 int sprintf (char*,char*,char*) ; 
 int sysfs_format_mac (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scsi_qla_host* to_qla_host (struct Scsi_Host*) ; 

__attribute__((used)) static int qla4xxx_host_get_param(struct Scsi_Host *shost,
				  enum iscsi_host_param param, char *buf)
{
	struct scsi_qla_host *ha = to_qla_host(shost);
	int len;

	switch (param) {
	case ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_format_mac(buf, ha->my_mac, MAC_ADDR_LEN);
		break;
	case ISCSI_HOST_PARAM_IPADDRESS:
		len = sprintf(buf, "%pI4\n", &ha->ip_config.ip_address);
		break;
	case ISCSI_HOST_PARAM_INITIATOR_NAME:
		len = sprintf(buf, "%s\n", ha->name_string);
		break;
	case ISCSI_HOST_PARAM_PORT_STATE:
		qla4xxx_set_port_state(shost);
		len = sprintf(buf, "%s\n", iscsi_get_port_state_name(shost));
		break;
	case ISCSI_HOST_PARAM_PORT_SPEED:
		qla4xxx_set_port_speed(shost);
		len = sprintf(buf, "%s\n", iscsi_get_port_speed_name(shost));
		break;
	default:
		return -ENOSYS;
	}

	return len;
}