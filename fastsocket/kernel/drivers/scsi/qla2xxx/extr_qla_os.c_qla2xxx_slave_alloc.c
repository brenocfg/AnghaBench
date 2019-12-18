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
struct scsi_device {int /*<<< orphan*/ * hostdata; } ;
struct fc_rport {scalar_t__ dd_data; } ;
typedef  int /*<<< orphan*/  fc_port_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ fc_remote_port_chkready (struct fc_rport*) ; 
 int /*<<< orphan*/  scsi_target (struct scsi_device*) ; 
 struct fc_rport* starget_to_rport (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla2xxx_slave_alloc(struct scsi_device *sdev)
{
	struct fc_rport *rport = starget_to_rport(scsi_target(sdev));

	if (!rport || fc_remote_port_chkready(rport))
		return -ENXIO;

	sdev->hostdata = *(fc_port_t **)rport->dd_data;

	return 0;
}