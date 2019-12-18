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
struct sysfs_entry {int /*<<< orphan*/  attr; scalar_t__ name; } ;
struct scsi_qla_host {struct Scsi_Host* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {TYPE_1__ shost_gendev; } ;

/* Variables and functions */
 struct sysfs_entry* bin_file_entries ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void qla4_8xxx_free_sysfs_attr(struct scsi_qla_host *ha)
{
	struct Scsi_Host *host = ha->host;
	struct sysfs_entry *iter;

	for (iter = bin_file_entries; iter->name; iter++)
		sysfs_remove_bin_file(&host->shost_gendev.kobj,
				      iter->attr);
}