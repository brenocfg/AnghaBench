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
struct ql4_boot_session_info {int dummy; } ;
struct TYPE_2__ {struct ql4_boot_session_info boot_pri_sess; } ;
struct scsi_qla_host {TYPE_1__ boot_tgt; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla4xxx_show_boot_tgt_info (struct ql4_boot_session_info*,int,char*) ; 

__attribute__((used)) static ssize_t qla4xxx_show_boot_tgt_pri_info(void *data, int type, char *buf)
{
	struct scsi_qla_host *ha = data;
	struct ql4_boot_session_info *boot_sess = &(ha->boot_tgt.boot_pri_sess);

	return qla4xxx_show_boot_tgt_info(boot_sess, type, buf);
}