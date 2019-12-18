#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct cxgbi_hba {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct cxgbi_device {char* dd_data; int /*<<< orphan*/  list_head; TYPE_1__ pmap; struct cxgbi_hba** hbas; struct net_device** ports; } ;

/* Variables and functions */
 int CXGBI_DBG_DEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cdev_list ; 
 int /*<<< orphan*/  cdev_mutex ; 
 struct cxgbi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct cxgbi_device *cxgbi_device_register(unsigned int extra,
					   unsigned int nports)
{
	struct cxgbi_device *cdev;

	cdev = kzalloc(sizeof(*cdev) + extra + nports *
			(sizeof(struct cxgbi_hba *) +
			 sizeof(struct net_device *)),
			GFP_KERNEL);
	if (!cdev) {
		pr_warn("nport %d, OOM.\n", nports);
		return NULL;
	}
	cdev->ports = (struct net_device **)(cdev + 1);
	cdev->hbas = (struct cxgbi_hba **)(((char*)cdev->ports) + nports *
						sizeof(struct net_device *));
	if (extra)
		cdev->dd_data = ((char *)cdev->hbas) +
				nports * sizeof(struct cxgbi_hba *);
	spin_lock_init(&cdev->pmap.lock);

	mutex_lock(&cdev_mutex);
	list_add_tail(&cdev->list_head, &cdev_list);
	mutex_unlock(&cdev_mutex);

	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u.\n", cdev, nports);
	return cdev;
}