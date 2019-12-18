#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* target_chap_name_length; char* target_secret_length; char* intr_chap_name_length; char* intr_secret_length; int /*<<< orphan*/  intr_secret; int /*<<< orphan*/  intr_chap_name; int /*<<< orphan*/  target_secret; int /*<<< orphan*/  target_chap_name; } ;
struct TYPE_3__ {int ip_type; int /*<<< orphan*/  ip_address; } ;
struct ql4_conn_info {int dest_port; TYPE_2__ chap; TYPE_1__ dest_ipaddr; } ;
struct ql4_boot_session_info {struct ql4_conn_info* conn_list; int /*<<< orphan*/  target_name; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_BOOT_TGT_CHAP_NAME 136 
#define  ISCSI_BOOT_TGT_CHAP_SECRET 135 
#define  ISCSI_BOOT_TGT_FLAGS 134 
#define  ISCSI_BOOT_TGT_IP_ADDR 133 
#define  ISCSI_BOOT_TGT_NAME 132 
#define  ISCSI_BOOT_TGT_NIC_ASSOC 131 
#define  ISCSI_BOOT_TGT_PORT 130 
#define  ISCSI_BOOT_TGT_REV_CHAP_NAME 129 
#define  ISCSI_BOOT_TGT_REV_CHAP_SECRET 128 
 int SYSFS_FLAG_FW_SEL_BOOT ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
qla4xxx_show_boot_tgt_info(struct ql4_boot_session_info *boot_sess, int type,
			   char *buf)
{
	struct ql4_conn_info *boot_conn = &boot_sess->conn_list[0];
	char *str = buf;
	int rc;

	switch (type) {
	case ISCSI_BOOT_TGT_NAME:
		rc = sprintf(buf, "%s\n", (char *)&boot_sess->target_name);
		break;
	case ISCSI_BOOT_TGT_IP_ADDR:
		if (boot_sess->conn_list[0].dest_ipaddr.ip_type == 0x1)
			rc = sprintf(buf, "%pI4\n",
				     &boot_conn->dest_ipaddr.ip_address);
		else
			rc = sprintf(str, "%pI6\n",
				     &boot_conn->dest_ipaddr.ip_address);
		break;
	case ISCSI_BOOT_TGT_PORT:
			rc = sprintf(str, "%d\n", boot_conn->dest_port);
		break;
	case ISCSI_BOOT_TGT_CHAP_NAME:
		rc = sprintf(str,  "%.*s\n",
			     boot_conn->chap.target_chap_name_length,
			     (char *)&boot_conn->chap.target_chap_name);
		break;
	case ISCSI_BOOT_TGT_CHAP_SECRET:
		rc = sprintf(str,  "%.*s\n",
			     boot_conn->chap.target_secret_length,
			     (char *)&boot_conn->chap.target_secret);
		break;
	case ISCSI_BOOT_TGT_REV_CHAP_NAME:
		rc = sprintf(str,  "%.*s\n",
			     boot_conn->chap.intr_chap_name_length,
			     (char *)&boot_conn->chap.intr_chap_name);
		break;
	case ISCSI_BOOT_TGT_REV_CHAP_SECRET:
		rc = sprintf(str,  "%.*s\n",
			     boot_conn->chap.intr_secret_length,
			     (char *)&boot_conn->chap.intr_secret);
		break;
	case ISCSI_BOOT_TGT_FLAGS:
		rc = sprintf(str, "%d\n", SYSFS_FLAG_FW_SEL_BOOT);
		break;
	case ISCSI_BOOT_TGT_NIC_ASSOC:
		rc = sprintf(str, "0\n");
		break;
	default:
		rc = -ENOSYS;
		break;
	}
	return rc;
}