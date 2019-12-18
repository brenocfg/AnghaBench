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
struct scsi_dh_data {scalar_t__ buf; int /*<<< orphan*/ * scsi_dh; } ;
struct scsi_device {TYPE_1__* request_queue; struct scsi_dh_data* scsi_dh_data; } ;
struct rdac_dh_data {TYPE_2__* ctlr; scalar_t__ lun_state; scalar_t__ mode; int /*<<< orphan*/  lun; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  kref; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue_lock; } ;

/* Variables and functions */
 int ARRAY_LABEL_LEN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  RDAC_NAME ; 
 int /*<<< orphan*/  RDAC_STATE_ACTIVE ; 
 int SCSI_DH_OK ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  UNINITIALIZED_LUN ; 
 int UNIQUE_ID_LEN ; 
 int check_ownership (struct scsi_device*,struct rdac_dh_data*) ; 
 int get_lun_info (struct scsi_device*,struct rdac_dh_data*,char*,char*) ; 
 int initialize_controller (struct scsi_device*,struct rdac_dh_data*,char*,char*) ; 
 int /*<<< orphan*/  kfree (struct scsi_dh_data*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct scsi_dh_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/ * lun_state ; 
 int /*<<< orphan*/ * mode ; 
 int /*<<< orphan*/  rdac_dh ; 
 int /*<<< orphan*/  release_controller ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ,...) ; 
 int set_mode_select (struct scsi_device*,struct rdac_dh_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdac_bus_attach(struct scsi_device *sdev)
{
	struct scsi_dh_data *scsi_dh_data;
	struct rdac_dh_data *h;
	unsigned long flags;
	int err;
	char array_name[ARRAY_LABEL_LEN];
	char array_id[UNIQUE_ID_LEN];

	scsi_dh_data = kzalloc(sizeof(*scsi_dh_data)
			       + sizeof(*h) , GFP_KERNEL);
	if (!scsi_dh_data) {
		sdev_printk(KERN_ERR, sdev, "%s: Attach failed\n",
			    RDAC_NAME);
		return -ENOMEM;
	}

	scsi_dh_data->scsi_dh = &rdac_dh;
	h = (struct rdac_dh_data *) scsi_dh_data->buf;
	h->lun = UNINITIALIZED_LUN;
	h->state = RDAC_STATE_ACTIVE;

	err = get_lun_info(sdev, h, array_name, array_id);
	if (err != SCSI_DH_OK)
		goto failed;

	err = initialize_controller(sdev, h, array_name, array_id);
	if (err != SCSI_DH_OK)
		goto failed;

	err = check_ownership(sdev, h);
	if (err != SCSI_DH_OK)
		goto clean_ctlr;

	err = set_mode_select(sdev, h);
	if (err != SCSI_DH_OK)
		goto clean_ctlr;

	if (!try_module_get(THIS_MODULE))
		goto clean_ctlr;

	spin_lock_irqsave(sdev->request_queue->queue_lock, flags);
	sdev->scsi_dh_data = scsi_dh_data;
	spin_unlock_irqrestore(sdev->request_queue->queue_lock, flags);

	sdev_printk(KERN_NOTICE, sdev,
		    "%s: LUN %d (%s) (%s)\n",
		    RDAC_NAME, h->lun, mode[(int)h->mode],
		    lun_state[(int)h->lun_state]);

	return 0;

clean_ctlr:
	spin_lock(&list_lock);
	kref_put(&h->ctlr->kref, release_controller);
	spin_unlock(&list_lock);

failed:
	kfree(scsi_dh_data);
	sdev_printk(KERN_ERR, sdev, "%s: not attached\n",
		    RDAC_NAME);
	return -EINVAL;
}