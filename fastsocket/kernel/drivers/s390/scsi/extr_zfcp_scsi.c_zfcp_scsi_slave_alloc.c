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
struct zfcp_unit {struct scsi_device* device; } ;
struct zfcp_adapter {int dummy; } ;
struct scsi_device {struct zfcp_unit* hostdata; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; TYPE_1__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  config_lock; } ;
struct TYPE_3__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_2__ zfcp_data ; 
 int /*<<< orphan*/  zfcp_unit_get (struct zfcp_unit*) ; 
 struct zfcp_unit* zfcp_unit_lookup (struct zfcp_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_scsi_slave_alloc(struct scsi_device *sdp)
{
	struct zfcp_adapter *adapter;
	struct zfcp_unit *unit;
	unsigned long flags;
	int retval = -ENXIO;

	adapter = (struct zfcp_adapter *) sdp->host->hostdata[0];
	if (!adapter)
		goto out;

	read_lock_irqsave(&zfcp_data.config_lock, flags);
	unit = zfcp_unit_lookup(adapter, sdp->channel, sdp->id, sdp->lun);
	if (unit) {
		sdp->hostdata = unit;
		unit->device = sdp;
		zfcp_unit_get(unit);
		retval = 0;
	}
	read_unlock_irqrestore(&zfcp_data.config_lock, flags);
out:
	return retval;
}