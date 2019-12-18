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
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {scalar_t__ function; int retries; struct dasd_device* startdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,char*) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int HZ ; 
 int /*<<< orphan*/  dasd_3990_erp_block_queue (struct dasd_ccw_req*,int) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_bus_out(struct dasd_ccw_req * erp)
{

	struct dasd_device *device = erp->startdev;

	/* first time set initial retry counter and erp_function */
	/* and retry once without blocking queue		 */
	/* (this enables easier enqueing of the cqr)		 */
	if (erp->function != dasd_3990_erp_bus_out) {
		erp->retries = 256;
		erp->function = dasd_3990_erp_bus_out;

	} else {

		/* issue a message and wait for 'device ready' interrupt */
		DBF_DEV_EVENT(DBF_WARNING, device, "%s",
			    "bus out parity error or BOPC requested by "
			    "channel");

		dasd_3990_erp_block_queue(erp, 60*HZ);

	}

	return erp;

}