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
struct sas_host_attrs {struct request_queue* q; } ;
struct request_queue {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 
 struct sas_host_attrs* to_sas_host_attrs (struct Scsi_Host*) ; 

__attribute__((used)) static void sas_host_release(struct device *dev)
{
	struct Scsi_Host *shost = dev_to_shost(dev);
	struct sas_host_attrs *sas_host = to_sas_host_attrs(shost);
	struct request_queue *q = sas_host->q;

	if (q)
		blk_cleanup_queue(q);
}