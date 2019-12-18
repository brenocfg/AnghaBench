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
struct cxgbi_hba {TYPE_1__* ndev; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum iscsi_host_param { ____Placeholder_iscsi_host_param } iscsi_host_param ;
typedef  char __be32 ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
 int ENODEV ; 
#define  ISCSI_HOST_PARAM_HWADDRESS 130 
#define  ISCSI_HOST_PARAM_IPADDRESS 129 
#define  ISCSI_HOST_PARAM_NETDEV_NAME 128 
 int /*<<< orphan*/  KERN_ERR ; 
 char cxgbi_get_iscsi_ipv4 (struct cxgbi_hba*) ; 
 int iscsi_host_get_param (struct Scsi_Host*,int,char*) ; 
 struct cxgbi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  log_debug (int,char*,char*,...) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 int sprintf (char*,char*,char*) ; 
 int sysfs_format_mac (char*,int /*<<< orphan*/ ,int) ; 

int cxgbi_get_host_param(struct Scsi_Host *shost, enum iscsi_host_param param,
			char *buf)
{
	struct cxgbi_hba *chba = iscsi_host_priv(shost);
	int len = 0;

	if (!chba->ndev) {
		shost_printk(KERN_ERR, shost, "Could not get host param. "
				"netdev for host not set.\n");
		return -ENODEV;
	}

	log_debug(1 << CXGBI_DBG_ISCSI,
		"shost 0x%p, hba 0x%p,%s, param %d.\n",
		shost, chba, chba->ndev->name, param);

	switch (param) {
	case ISCSI_HOST_PARAM_HWADDRESS:
		len = sysfs_format_mac(buf, chba->ndev->dev_addr, 6);
		break;
	case ISCSI_HOST_PARAM_NETDEV_NAME:
		len = sprintf(buf, "%s\n", chba->ndev->name);
		break;
	case ISCSI_HOST_PARAM_IPADDRESS:
	{
		__be32 addr;

		addr = cxgbi_get_iscsi_ipv4(chba);
		len = sprintf(buf, "%pI4", &addr);
		log_debug(1 << CXGBI_DBG_ISCSI,
			"hba %s, ipv4 %pI4.\n", chba->ndev->name, &addr);
		break;
	}
	default:
		return iscsi_host_get_param(shost, param, buf);
	}

	return len;
}