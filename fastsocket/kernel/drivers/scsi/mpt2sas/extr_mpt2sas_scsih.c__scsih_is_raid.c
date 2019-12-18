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
struct scsi_device {scalar_t__ channel; int /*<<< orphan*/  host; } ;
struct device {int dummy; } ;
struct MPT2SAS_ADAPTER {scalar_t__ is_warpdrive; } ;

/* Variables and functions */
 scalar_t__ RAID_CHANNEL ; 
 struct MPT2SAS_ADAPTER* shost_priv (int /*<<< orphan*/ ) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static int
_scsih_is_raid(struct device *dev)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	struct MPT2SAS_ADAPTER *ioc = shost_priv(sdev->host);

	if (ioc->is_warpdrive)
		return 0;
	return (sdev->channel == RAID_CHANNEL) ? 1 : 0;
}