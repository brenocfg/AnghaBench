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
typedef  int ssize_t ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_BOOT_ETH_FLAGS 130 
#define  ISCSI_BOOT_ETH_INDEX 129 
#define  ISCSI_BOOT_ETH_MAC 128 
 int beiscsi_get_macaddr (char*,struct beiscsi_hba*) ; 
 int sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t beiscsi_show_boot_eth_info(void *data, int type, char *buf)
{
	struct beiscsi_hba *phba = data;
	char *str = buf;
	int rc;

	switch (type) {
	case ISCSI_BOOT_ETH_FLAGS:
		rc = sprintf(str, "2\n");
		break;
	case ISCSI_BOOT_ETH_INDEX:
		rc = sprintf(str, "0\n");
		break;
	case ISCSI_BOOT_ETH_MAC:
		rc  = beiscsi_get_macaddr(str, phba);
		break;
	default:
		rc = -ENOSYS;
		break;
	}
	return rc;
}