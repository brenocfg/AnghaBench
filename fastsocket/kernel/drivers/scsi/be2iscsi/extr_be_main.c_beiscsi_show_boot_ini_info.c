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
struct TYPE_2__ {char* initiator_iscsiname; } ;
struct beiscsi_hba {TYPE_1__ boot_sess; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_BOOT_INI_INITIATOR_NAME 128 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t beiscsi_show_boot_ini_info(void *data, int type, char *buf)
{
	struct beiscsi_hba *phba = data;
	char *str = buf;
	int rc;

	switch (type) {
	case ISCSI_BOOT_INI_INITIATOR_NAME:
		rc = sprintf(str, "%s\n", phba->boot_sess.initiator_iscsiname);
		break;
	default:
		rc = -ENOSYS;
		break;
	}
	return rc;
}