#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ptp_clock_info {scalar_t__ n_alarm; int /*<<< orphan*/  owner; scalar_t__ pps; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ptp_clock {int index; int /*<<< orphan*/  tsevq_mux; int /*<<< orphan*/  devid; scalar_t__ pps_source; TYPE_2__ clock; int /*<<< orphan*/  dev; int /*<<< orphan*/  tsev_wq; TYPE_1__ tsevq; struct ptp_clock_info* info; } ;
struct pps_source_info {int /*<<< orphan*/  owner; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  pps ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ptp_clock* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ MINORMASK ; 
 int /*<<< orphan*/  MKDEV (int,int) ; 
 int /*<<< orphan*/  PPS_MAX_NAME_LEN ; 
 scalar_t__ PTP_MAX_ALARMS ; 
 int /*<<< orphan*/  PTP_PPS_DEFAULTS ; 
 int /*<<< orphan*/  PTP_PPS_MODE ; 
 int /*<<< orphan*/  delete_ptp_clock ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,struct ptp_clock*) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct ptp_clock*,char*,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ptp_clock*) ; 
 struct ptp_clock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pps_source_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int posix_clock_register (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pps_register_source (struct pps_source_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pps_unregister_source (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  ptp_class ; 
 int /*<<< orphan*/  ptp_cleanup_sysfs (struct ptp_clock*) ; 
 int /*<<< orphan*/  ptp_clock_ops ; 
 int /*<<< orphan*/  ptp_clocks_map ; 
 int /*<<< orphan*/  ptp_devt ; 
 int ptp_populate_sysfs (struct ptp_clock*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ptp_clock *ptp_clock_register(struct ptp_clock_info *info,
				     struct device *parent)
{
	struct ptp_clock *ptp;
	int err = 0, index, major = MAJOR(ptp_devt);

	if (info->n_alarm > PTP_MAX_ALARMS)
		return ERR_PTR(-EINVAL);

	/* Initialize a clock structure. */
	err = -ENOMEM;
	ptp = kzalloc(sizeof(struct ptp_clock), GFP_KERNEL);
	if (ptp == NULL)
		goto no_memory;

	index = ida_simple_get(&ptp_clocks_map, 0, MINORMASK + 1, GFP_KERNEL);
	if (index < 0) {
		err = index;
		goto no_slot;
	}

	ptp->clock.ops = ptp_clock_ops;
	ptp->clock.release = delete_ptp_clock;
	ptp->info = info;
	ptp->devid = MKDEV(major, index);
	ptp->index = index;
	spin_lock_init(&ptp->tsevq.lock);
	mutex_init(&ptp->tsevq_mux);
	init_waitqueue_head(&ptp->tsev_wq);

	/* Create a new device in our class. */
	ptp->dev = device_create(ptp_class, parent, ptp->devid, ptp,
				 "ptp%d", ptp->index);
	if (IS_ERR(ptp->dev))
		goto no_device;

	dev_set_drvdata(ptp->dev, ptp);

	err = ptp_populate_sysfs(ptp);
	if (err)
		goto no_sysfs;

	/* Register a new PPS source. */
	if (info->pps) {
		struct pps_source_info pps;
		memset(&pps, 0, sizeof(pps));
		snprintf(pps.name, PPS_MAX_NAME_LEN, "ptp%d", index);
		pps.mode = PTP_PPS_MODE;
		pps.owner = info->owner;
		ptp->pps_source = pps_register_source(&pps, PTP_PPS_DEFAULTS);
		if (!ptp->pps_source) {
			pr_err("failed to register pps source\n");
			goto no_pps;
		}
	}

	/* Create a posix clock. */
	err = posix_clock_register(&ptp->clock, ptp->devid);
	if (err) {
		pr_err("failed to create posix clock\n");
		goto no_clock;
	}

	return ptp;

no_clock:
	if (ptp->pps_source)
		pps_unregister_source(ptp->pps_source);
no_pps:
	ptp_cleanup_sysfs(ptp);
no_sysfs:
	device_destroy(ptp_class, ptp->devid);
no_device:
	mutex_destroy(&ptp->tsevq_mux);
no_slot:
	kfree(ptp);
no_memory:
	return ERR_PTR(err);
}