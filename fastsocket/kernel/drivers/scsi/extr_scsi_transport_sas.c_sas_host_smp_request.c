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
struct request_queue {scalar_t__ queuedata; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sas_smp_request (struct request_queue*,struct Scsi_Host*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sas_host_smp_request(struct request_queue *q)
{
	sas_smp_request(q, (struct Scsi_Host *)q->queuedata, NULL);
}