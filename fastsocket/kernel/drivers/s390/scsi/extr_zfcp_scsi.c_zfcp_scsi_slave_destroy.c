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
struct zfcp_unit {int /*<<< orphan*/ * device; } ;
struct scsi_device {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_unit_put (struct zfcp_unit*) ; 

__attribute__((used)) static void zfcp_scsi_slave_destroy(struct scsi_device *sdpnt)
{
	struct zfcp_unit *unit = (struct zfcp_unit *) sdpnt->hostdata;

	/* if previous slave_alloc returned early, there is nothing to do */
	if (!unit)
		return;

	unit->device = NULL;
	zfcp_unit_put(unit);
}