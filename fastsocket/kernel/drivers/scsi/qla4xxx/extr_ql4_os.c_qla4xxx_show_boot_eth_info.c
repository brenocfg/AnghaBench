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
struct scsi_qla_host {int /*<<< orphan*/  my_mac; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_BOOT_ETH_FLAGS 130 
#define  ISCSI_BOOT_ETH_INDEX 129 
#define  ISCSI_BOOT_ETH_MAC 128 
 int /*<<< orphan*/  MAC_ADDR_LEN ; 
 int SYSFS_FLAG_FW_SEL_BOOT ; 
 int sprintf (char*,char*,...) ; 
 int sysfs_format_mac (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t qla4xxx_show_boot_eth_info(void *data, int type, char *buf)
{
	struct scsi_qla_host *ha = data;
	char *str = buf;
	int rc;

	switch (type) {
	case ISCSI_BOOT_ETH_FLAGS:
		rc = sprintf(str, "%d\n", SYSFS_FLAG_FW_SEL_BOOT);
		break;
	case ISCSI_BOOT_ETH_INDEX:
		rc = sprintf(str, "0\n");
		break;
	case ISCSI_BOOT_ETH_MAC:
		rc = sysfs_format_mac(str, ha->my_mac,
				      MAC_ADDR_LEN);
		break;
	default:
		rc = -ENOSYS;
		break;
	}
	return rc;
}