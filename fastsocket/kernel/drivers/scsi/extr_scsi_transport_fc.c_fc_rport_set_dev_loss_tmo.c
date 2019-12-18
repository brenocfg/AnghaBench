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
struct fc_rport {scalar_t__ port_state; int fast_io_fail_tmo; } ;
struct fc_internal {TYPE_1__* f; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_rport_dev_loss_tmo ) (struct fc_rport*,unsigned long) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ FC_PORTSTATE_BLOCKED ; 
 scalar_t__ FC_PORTSTATE_DELETED ; 
 scalar_t__ FC_PORTSTATE_NOTPRESENT ; 
 unsigned long SCSI_DEVICE_BLOCK_MAX_TIMEOUT ; 
 unsigned long UINT_MAX ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  stub1 (struct fc_rport*,unsigned long) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_rport_set_dev_loss_tmo(struct fc_rport *rport,
				     unsigned long val)
{
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct fc_internal *i = to_fc_internal(shost->transportt);

	if ((rport->port_state == FC_PORTSTATE_BLOCKED) ||
	    (rport->port_state == FC_PORTSTATE_DELETED) ||
	    (rport->port_state == FC_PORTSTATE_NOTPRESENT))
		return -EBUSY;
	/*
	 * Check for overflow; dev_loss_tmo is u32
	 */
	if (val > UINT_MAX)
		return -EINVAL;

	/*
	 * If fast_io_fail is off we have to cap
	 * dev_loss_tmo at SCSI_DEVICE_BLOCK_MAX_TIMEOUT
	 */
	if (rport->fast_io_fail_tmo == -1 &&
	    val > SCSI_DEVICE_BLOCK_MAX_TIMEOUT)
		return -EINVAL;

	i->f->set_rport_dev_loss_tmo(rport, val);
	return 0;
}