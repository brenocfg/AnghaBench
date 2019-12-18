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
struct beiscsi_hba {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum iscsi_host_param { ____Placeholder_iscsi_host_param } iscsi_host_param ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
#define  ISCSI_HOST_PARAM_HWADDRESS 131 
#define  ISCSI_HOST_PARAM_INITIATOR_NAME 130 
#define  ISCSI_HOST_PARAM_PORT_SPEED 129 
#define  ISCSI_HOST_PARAM_PORT_STATE 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int beiscsi_get_initname (char*,struct beiscsi_hba*) ; 
 int beiscsi_get_macaddr (char*,struct beiscsi_hba*) ; 
 int beiscsi_get_port_speed (struct Scsi_Host*) ; 
 int /*<<< orphan*/  beiscsi_get_port_state (struct Scsi_Host*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 char* iscsi_get_port_speed_name (struct Scsi_Host*) ; 
 char* iscsi_get_port_state_name (struct Scsi_Host*) ; 
 int iscsi_host_get_param (struct Scsi_Host*,int,char*) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 int sprintf (char*,char*,char*) ; 

int beiscsi_get_host_param(struct Scsi_Host *shost,
			   enum iscsi_host_param param, char *buf)
{
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	int status = 0;

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_get_host_param,"
		    " param= %d\n", param);

	switch (param) {
	case ISCSI_HOST_PARAM_HWADDRESS:
		status = beiscsi_get_macaddr(buf, phba);
		if (status < 0) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : beiscsi_get_macaddr Failed\n");
			return status;
		}
		break;
	case ISCSI_HOST_PARAM_INITIATOR_NAME:
		status = beiscsi_get_initname(buf, phba);
		if (status < 0) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : Retreiving Initiator Name Failed\n");
			return status;
		}
		break;
	case ISCSI_HOST_PARAM_PORT_STATE:
		beiscsi_get_port_state(shost);
		status = sprintf(buf, "%s\n", iscsi_get_port_state_name(shost));
		break;
	case ISCSI_HOST_PARAM_PORT_SPEED:
		status = beiscsi_get_port_speed(shost);
		if (status) {
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : Retreiving Port Speed Failed\n");
			return status;
		}
		status = sprintf(buf, "%s\n", iscsi_get_port_speed_name(shost));
		break;
	default:
		return iscsi_host_get_param(shost, param, buf);
	}
	return status;
}