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
struct cnic_uio_dev {int /*<<< orphan*/ * l2_ring; int /*<<< orphan*/  l2_ring_map; int /*<<< orphan*/  l2_ring_size; TYPE_1__* pdev; int /*<<< orphan*/ * l2_buf; int /*<<< orphan*/  l2_buf_map; int /*<<< orphan*/  l2_buf_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cnic_free_uio_rings(struct cnic_uio_dev *udev)
{
	if (udev->l2_buf) {
		dma_free_coherent(&udev->pdev->dev, udev->l2_buf_size,
				  udev->l2_buf, udev->l2_buf_map);
		udev->l2_buf = NULL;
	}

	if (udev->l2_ring) {
		dma_free_coherent(&udev->pdev->dev, udev->l2_ring_size,
				  udev->l2_ring, udev->l2_ring_map);
		udev->l2_ring = NULL;
	}

}