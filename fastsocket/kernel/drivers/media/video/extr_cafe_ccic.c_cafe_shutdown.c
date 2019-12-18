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
struct cafe_camera {scalar_t__ n_sbufs; int /*<<< orphan*/  vdev; int /*<<< orphan*/  regs; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cafe_ctlr_power_down (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_ctlr_stop_dma (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_free_dma_bufs (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_free_sio_buffers (struct cafe_camera*) ; 
 int /*<<< orphan*/  cafe_smbus_shutdown (struct cafe_camera*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cafe_camera*) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cafe_shutdown(struct cafe_camera *cam)
{
/* FIXME: Make sure we take care of everything here */
	if (cam->n_sbufs > 0)
		/* What if they are still mapped?  Shouldn't be, but... */
		cafe_free_sio_buffers(cam);
	cafe_ctlr_stop_dma(cam);
	cafe_ctlr_power_down(cam);
	cafe_smbus_shutdown(cam);
	cafe_free_dma_bufs(cam);
	free_irq(cam->pdev->irq, cam);
	pci_iounmap(cam->pdev, cam->regs);
	video_unregister_device(&cam->vdev);
}