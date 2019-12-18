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
typedef  void* uint ;
struct iscsi_scan_data {void* lun; void* id; void* channel; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int device_for_each_child (int /*<<< orphan*/ *,struct iscsi_scan_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_user_scan_session ; 

__attribute__((used)) static int iscsi_user_scan(struct Scsi_Host *shost, uint channel,
			   uint id, uint lun)
{
	struct iscsi_scan_data scan_data;

	scan_data.channel = channel;
	scan_data.id = id;
	scan_data.lun = lun;

	return device_for_each_child(&shost->shost_gendev, &scan_data,
				     iscsi_user_scan_session);
}