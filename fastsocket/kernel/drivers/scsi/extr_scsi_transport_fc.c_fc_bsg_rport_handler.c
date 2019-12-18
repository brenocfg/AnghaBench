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
struct request_queue {struct fc_rport* queuedata; } ;
struct fc_rport {int /*<<< orphan*/  dev; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_bsg_request_handler (struct request_queue*,struct Scsi_Host*,struct fc_rport*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 

__attribute__((used)) static void
fc_bsg_rport_handler(struct request_queue *q)
{
	struct fc_rport *rport = q->queuedata;
	struct Scsi_Host *shost = rport_to_shost(rport);

	fc_bsg_request_handler(q, shost, rport, &rport->dev);
}