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
struct iscsi_iface_param_info {int param; int* value; } ;
struct beiscsi_hba {int /*<<< orphan*/  ipv4_iface; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int ISCSI_BOOTPROTO_DHCP ; 
 int ISCSI_BOOTPROTO_STATIC ; 
 int ISCSI_IFACE_ENABLE ; 
#define  ISCSI_NET_PARAM_IFACE_ENABLE 134 
#define  ISCSI_NET_PARAM_IPV4_ADDR 133 
#define  ISCSI_NET_PARAM_IPV4_BOOTPROTO 132 
#define  ISCSI_NET_PARAM_IPV4_GW 131 
#define  ISCSI_NET_PARAM_IPV4_SUBNET 130 
#define  ISCSI_NET_PARAM_VLAN_ENABLED 129 
#define  ISCSI_NET_PARAM_VLAN_TAG 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int beiscsi_create_ipv4_iface (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int beiscsi_set_static_ip (struct Scsi_Host*,struct iscsi_iface_param_info*,void*,int /*<<< orphan*/ ) ; 
 int beiscsi_set_vlan_tag (struct Scsi_Host*,struct iscsi_iface_param_info*) ; 
 int /*<<< orphan*/  iscsi_destroy_iface (int /*<<< orphan*/ ) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 int mgmt_set_gateway (struct beiscsi_hba*,struct iscsi_iface_param_info*) ; 
 int mgmt_set_ip (struct beiscsi_hba*,struct iscsi_iface_param_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
beiscsi_set_ipv4(struct Scsi_Host *shost,
		struct iscsi_iface_param_info *iface_param,
		void *data, uint32_t dt_len)
{
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	int ret = 0;

	/* Check the param */
	switch (iface_param->param) {
	case ISCSI_NET_PARAM_IPV4_GW:
		ret = mgmt_set_gateway(phba, iface_param);
		break;
	case ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		if (iface_param->value[0] == ISCSI_BOOTPROTO_DHCP)
			ret = mgmt_set_ip(phba, iface_param,
					NULL, ISCSI_BOOTPROTO_DHCP);
		else if (iface_param->value[0] == ISCSI_BOOTPROTO_STATIC)
			ret = beiscsi_set_static_ip(shost, iface_param,
						    data, dt_len);
		else
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : Invalid BOOTPROTO: %d\n",
				    iface_param->value[0]);
		break;
	case ISCSI_NET_PARAM_IFACE_ENABLE:
		if (iface_param->value[0] == ISCSI_IFACE_ENABLE)
			ret = beiscsi_create_ipv4_iface(phba);
		else
			iscsi_destroy_iface(phba->ipv4_iface);
		break;
	case ISCSI_NET_PARAM_IPV4_SUBNET:
	case ISCSI_NET_PARAM_IPV4_ADDR:
		ret = beiscsi_set_static_ip(shost, iface_param,
					    data, dt_len);
		break;
	case ISCSI_NET_PARAM_VLAN_ENABLED:
	case ISCSI_NET_PARAM_VLAN_TAG:
		ret = beiscsi_set_vlan_tag(shost, iface_param);
		break;
	default:
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Param %d not supported\n",
			    iface_param->param);
	}

	return ret;
}