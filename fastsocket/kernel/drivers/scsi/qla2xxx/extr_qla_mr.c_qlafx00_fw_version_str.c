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
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct TYPE_2__ {char* fw_version; } ;
struct qla_hw_data {TYPE_1__ mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

char *
qlafx00_fw_version_str(struct scsi_qla_host *vha, char *str)
{
	struct qla_hw_data *ha = vha->hw;

	sprintf(str, "%s", ha->mr.fw_version);
	return str;
}