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
struct dasd_device {int /*<<< orphan*/  eer_cqr; } ;
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
#define  DASD_EER_FATALERROR 131 
#define  DASD_EER_NOPATH 130 
#define  DASD_EER_PPRCSUSPEND 129 
#define  DASD_EER_STATECHANGE 128 
 int /*<<< orphan*/  dasd_eer_write_snss_trigger (struct dasd_device*,struct dasd_ccw_req*,unsigned int) ; 
 int /*<<< orphan*/  dasd_eer_write_standard_trigger (struct dasd_device*,struct dasd_ccw_req*,unsigned int) ; 

void dasd_eer_write(struct dasd_device *device, struct dasd_ccw_req *cqr,
		    unsigned int id)
{
	if (!device->eer_cqr)
		return;
	switch (id) {
	case DASD_EER_FATALERROR:
	case DASD_EER_PPRCSUSPEND:
		dasd_eer_write_standard_trigger(device, cqr, id);
		break;
	case DASD_EER_NOPATH:
		dasd_eer_write_standard_trigger(device, NULL, id);
		break;
	case DASD_EER_STATECHANGE:
		dasd_eer_write_snss_trigger(device, cqr, id);
		break;
	default: /* unknown trigger, so we write it without any sense data */
		dasd_eer_write_standard_trigger(device, NULL, id);
		break;
	}
}