#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  ep_qh_dma; int /*<<< orphan*/  ep_qh; int /*<<< orphan*/  ep_qh_size; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* udc_controller ; 

__attribute__((used)) static void fsl_udc_release(struct device *dev)
{
	complete(udc_controller->done);
	dma_free_coherent(dev->parent, udc_controller->ep_qh_size,
			udc_controller->ep_qh, udc_controller->ep_qh_dma);
	kfree(udc_controller);
}