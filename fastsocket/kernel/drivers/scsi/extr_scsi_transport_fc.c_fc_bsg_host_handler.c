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
struct request_queue {struct Scsi_Host* queuedata; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_bsg_request_handler (struct request_queue*,struct Scsi_Host*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fc_bsg_host_handler(struct request_queue *q)
{
	struct Scsi_Host *shost = q->queuedata;

	fc_bsg_request_handler(q, shost, NULL, &shost->shost_gendev);
}