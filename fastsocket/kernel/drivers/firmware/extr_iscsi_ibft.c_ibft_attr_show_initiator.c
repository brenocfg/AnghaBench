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
struct ibft_kobject {void* header; struct ibft_initiator* initiator; } ;
struct TYPE_2__ {int index; int flags; } ;
struct ibft_initiator {int /*<<< orphan*/  initiator_name_off; int /*<<< orphan*/  initiator_name_len; int /*<<< orphan*/  sec_radius_server; int /*<<< orphan*/  pri_radius_server; int /*<<< orphan*/  slp_server; int /*<<< orphan*/  isns_server; TYPE_1__ hdr; } ;
typedef  int ssize_t ;

/* Variables and functions */
#define  ISCSI_BOOT_INI_FLAGS 134 
#define  ISCSI_BOOT_INI_INDEX 133 
#define  ISCSI_BOOT_INI_INITIATOR_NAME 132 
#define  ISCSI_BOOT_INI_ISNS_SERVER 131 
#define  ISCSI_BOOT_INI_PRI_RADIUS_SERVER 130 
#define  ISCSI_BOOT_INI_SEC_RADIUS_SERVER 129 
#define  ISCSI_BOOT_INI_SLP_SERVER 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf_ipaddr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf_string (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t ibft_attr_show_initiator(void *data, int type, char *buf)
{
	struct ibft_kobject *entry = data;
	struct ibft_initiator *initiator = entry->initiator;
	void *ibft_loc = entry->header;
	char *str = buf;

	if (!initiator)
		return 0;

	switch (type) {
	case ISCSI_BOOT_INI_INDEX:
		str += sprintf(str, "%d\n", initiator->hdr.index);
		break;
	case ISCSI_BOOT_INI_FLAGS:
		str += sprintf(str, "%d\n", initiator->hdr.flags);
		break;
	case ISCSI_BOOT_INI_ISNS_SERVER:
		str += sprintf_ipaddr(str, initiator->isns_server);
		break;
	case ISCSI_BOOT_INI_SLP_SERVER:
		str += sprintf_ipaddr(str, initiator->slp_server);
		break;
	case ISCSI_BOOT_INI_PRI_RADIUS_SERVER:
		str += sprintf_ipaddr(str, initiator->pri_radius_server);
		break;
	case ISCSI_BOOT_INI_SEC_RADIUS_SERVER:
		str += sprintf_ipaddr(str, initiator->sec_radius_server);
		break;
	case ISCSI_BOOT_INI_INITIATOR_NAME:
		str += sprintf_string(str, initiator->initiator_name_len,
				      (char *)ibft_loc +
				      initiator->initiator_name_off);
		break;
	default:
		break;
	}

	return str - buf;
}