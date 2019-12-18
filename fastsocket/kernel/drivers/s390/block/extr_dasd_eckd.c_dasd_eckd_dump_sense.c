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
struct irb {int /*<<< orphan*/  scsw; } ;
struct dasd_device {int dummy; } ;
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_eckd_dump_sense_ccw (struct dasd_device*,struct dasd_ccw_req*,struct irb*) ; 
 int /*<<< orphan*/  dasd_eckd_dump_sense_tcw (struct dasd_device*,struct dasd_ccw_req*,struct irb*) ; 
 scalar_t__ scsw_is_tm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eckd_dump_sense(struct dasd_device *device,
				 struct dasd_ccw_req *req, struct irb *irb)
{
	if (scsw_is_tm(&irb->scsw))
		dasd_eckd_dump_sense_tcw(device, req, irb);
	else
		dasd_eckd_dump_sense_ccw(device, req, irb);
}