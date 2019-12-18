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
struct iscsi_iface {int dummy; } ;
struct beiscsi_hba {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct be_cmd_get_def_gateway_resp {TYPE_1__ ip_addr; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  gateway ;
typedef  enum iscsi_param_type { ____Placeholder_iscsi_param_type } iscsi_param_type ;

/* Variables and functions */
 int /*<<< orphan*/  BE2_IPV4 ; 
 int ENOSYS ; 
#define  ISCSI_NET_PARAM_IFACE_ENABLE 136 
#define  ISCSI_NET_PARAM_IPV4_ADDR 135 
#define  ISCSI_NET_PARAM_IPV4_BOOTPROTO 134 
#define  ISCSI_NET_PARAM_IPV4_GW 133 
#define  ISCSI_NET_PARAM_IPV4_SUBNET 132 
#define  ISCSI_NET_PARAM_IPV6_ADDR 131 
#define  ISCSI_NET_PARAM_VLAN_ENABLED 130 
#define  ISCSI_NET_PARAM_VLAN_ID 129 
#define  ISCSI_NET_PARAM_VLAN_PRIORITY 128 
 int be2iscsi_get_if_param (struct beiscsi_hba*,struct iscsi_iface*,int,char*) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* iscsi_iface_to_shost (struct iscsi_iface*) ; 
 int /*<<< orphan*/  memset (struct be_cmd_get_def_gateway_resp*,int /*<<< orphan*/ ,int) ; 
 int mgmt_get_gateway (struct beiscsi_hba*,int /*<<< orphan*/ ,struct be_cmd_get_def_gateway_resp*) ; 
 int sprintf (char*,char*,...) ; 

int be2iscsi_iface_get_param(struct iscsi_iface *iface,
		enum iscsi_param_type param_type,
		int param, char *buf)
{
	struct Scsi_Host *shost = iscsi_iface_to_shost(iface);
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	struct be_cmd_get_def_gateway_resp gateway;
	int len = -ENOSYS;

	switch (param) {
	case ISCSI_NET_PARAM_IPV4_ADDR:
	case ISCSI_NET_PARAM_IPV4_SUBNET:
	case ISCSI_NET_PARAM_IPV4_BOOTPROTO:
	case ISCSI_NET_PARAM_IPV6_ADDR:
	case ISCSI_NET_PARAM_VLAN_ENABLED:
	case ISCSI_NET_PARAM_VLAN_ID:
	case ISCSI_NET_PARAM_VLAN_PRIORITY:
		len = be2iscsi_get_if_param(phba, iface, param, buf);
		break;
	case ISCSI_NET_PARAM_IFACE_ENABLE:
		len = sprintf(buf, "enabled\n");
		break;
	case ISCSI_NET_PARAM_IPV4_GW:
		memset(&gateway, 0, sizeof(gateway));
		len = mgmt_get_gateway(phba, BE2_IPV4, &gateway);
		if (!len)
			len = sprintf(buf, "%pI4\n", &gateway.ip_addr.addr);
		break;
	default:
		len = -ENOSYS;
	}

	return len;
}