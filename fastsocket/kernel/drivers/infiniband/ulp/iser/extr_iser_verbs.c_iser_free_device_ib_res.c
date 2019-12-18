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
struct iser_device {int cqs_used; int /*<<< orphan*/ * pd; int /*<<< orphan*/ * mr; int /*<<< orphan*/  cq_desc; int /*<<< orphan*/  event_handler; int /*<<< orphan*/ ** rx_cq; int /*<<< orphan*/ ** tx_cq; int /*<<< orphan*/ * cq_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dereg_mr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_event_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iser_free_device_ib_res(struct iser_device *device)
{
	int i;
	BUG_ON(device->mr == NULL);

	for (i = 0; i < device->cqs_used; i++) {
		tasklet_kill(&device->cq_tasklet[i]);
		(void)ib_destroy_cq(device->tx_cq[i]);
		(void)ib_destroy_cq(device->rx_cq[i]);
		device->tx_cq[i] = NULL;
		device->rx_cq[i] = NULL;
	}

	(void)ib_unregister_event_handler(&device->event_handler);
	(void)ib_dereg_mr(device->mr);
	(void)ib_dealloc_pd(device->pd);

	kfree(device->cq_desc);

	device->mr = NULL;
	device->pd = NULL;
}