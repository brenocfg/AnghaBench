#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct sas_rphy {int host_no; struct request_queue* q; struct device shost_gendev; struct device dev; TYPE_2__* hostt; int /*<<< orphan*/  transportt; } ;
struct request_queue {struct sas_rphy* queuedata; } ;
struct Scsi_Host {int host_no; struct request_queue* q; struct device shost_gendev; struct device dev; TYPE_2__* hostt; int /*<<< orphan*/  transportt; } ;
typedef  int /*<<< orphan*/  namebuf ;
struct TYPE_8__ {struct request_queue* q; } ;
struct TYPE_7__ {TYPE_1__* f; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  smp_handler; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QUEUE_FLAG_BIDI ; 
 int /*<<< orphan*/  blk_cleanup_queue (struct request_queue*) ; 
 struct request_queue* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bsg_register_queue (struct request_queue*,struct device*,char const*,void (*) (struct device*)) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_flag_set_unlocked (int /*<<< orphan*/ ,struct request_queue*) ; 
 void sas_host_release (struct device*) ; 
 int /*<<< orphan*/  sas_host_smp_request ; 
 int /*<<< orphan*/  sas_non_host_smp_request ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 TYPE_4__* to_sas_host_attrs (struct sas_rphy*) ; 
 TYPE_3__* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sas_bsg_initialize(struct Scsi_Host *shost, struct sas_rphy *rphy)
{
	struct request_queue *q;
	int error;
	struct device *dev;
	char namebuf[20];
	const char *name;
	void (*release)(struct device *);

	if (!to_sas_internal(shost->transportt)->f->smp_handler) {
		printk("%s can't handle SMP requests\n", shost->hostt->name);
		return 0;
	}

	if (rphy) {
		q = blk_init_queue(sas_non_host_smp_request, NULL);
		dev = &rphy->dev;
		name = dev_name(dev);
		release = NULL;
	} else {
		q = blk_init_queue(sas_host_smp_request, NULL);
		dev = &shost->shost_gendev;
		snprintf(namebuf, sizeof(namebuf),
			 "sas_host%d", shost->host_no);
		name = namebuf;
		release = sas_host_release;
	}
	if (!q)
		return -ENOMEM;

	error = bsg_register_queue(q, dev, name, release);
	if (error) {
		blk_cleanup_queue(q);
		return -ENOMEM;
	}

	if (rphy)
		rphy->q = q;
	else
		to_sas_host_attrs(shost)->q = q;

	if (rphy)
		q->queuedata = rphy;
	else
		q->queuedata = shost;

	queue_flag_set_unlocked(QUEUE_FLAG_BIDI, q);
	return 0;
}