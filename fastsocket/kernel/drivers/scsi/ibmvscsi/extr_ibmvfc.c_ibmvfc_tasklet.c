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
struct vio_dev {int dummy; } ;
struct ibmvfc_host {TYPE_1__* host; int /*<<< orphan*/  dev; } ;
struct ibmvfc_crq {scalar_t__ valid; } ;
struct ibmvfc_async_crq {scalar_t__ valid; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibmvfc_handle_async (struct ibmvfc_async_crq*,struct ibmvfc_host*) ; 
 int /*<<< orphan*/  ibmvfc_handle_crq (struct ibmvfc_crq*,struct ibmvfc_host*) ; 
 struct ibmvfc_async_crq* ibmvfc_next_async_crq (struct ibmvfc_host*) ; 
 struct ibmvfc_crq* ibmvfc_next_crq (struct ibmvfc_host*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_disable_interrupts (struct vio_dev*) ; 
 int /*<<< orphan*/  vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static void ibmvfc_tasklet(void *data)
{
	struct ibmvfc_host *vhost = data;
	struct vio_dev *vdev = to_vio_dev(vhost->dev);
	struct ibmvfc_crq *crq;
	struct ibmvfc_async_crq *async;
	unsigned long flags;
	int done = 0;

	spin_lock_irqsave(vhost->host->host_lock, flags);
	while (!done) {
		/* Pull all the valid messages off the async CRQ */
		while ((async = ibmvfc_next_async_crq(vhost)) != NULL) {
			ibmvfc_handle_async(async, vhost);
			mb();
			async->valid = 0;
		}

		/* Pull all the valid messages off the CRQ */
		while ((crq = ibmvfc_next_crq(vhost)) != NULL) {
			ibmvfc_handle_crq(crq, vhost);
			mb();
			crq->valid = 0;
		}

		vio_enable_interrupts(vdev);
		if ((async = ibmvfc_next_async_crq(vhost)) != NULL) {
			vio_disable_interrupts(vdev);
			ibmvfc_handle_async(async, vhost);
			mb();
			async->valid = 0;
		} else if ((crq = ibmvfc_next_crq(vhost)) != NULL) {
			vio_disable_interrupts(vdev);
			ibmvfc_handle_crq(crq, vhost);
			mb();
			crq->valid = 0;
		} else
			done = 1;
	}

	spin_unlock_irqrestore(vhost->host->host_lock, flags);
}