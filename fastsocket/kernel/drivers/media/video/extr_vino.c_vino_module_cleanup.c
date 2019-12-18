#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  dma; int /*<<< orphan*/ * dma_cpu; } ;
struct TYPE_7__ {int /*<<< orphan*/ * vdev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * vdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  dummy_page; TYPE_3__ dummy_desc_table; TYPE_2__ a; TYPE_1__ b; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SGI_VINO_IRQ ; 
 int VINO_DUMMY_DESC_COUNT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vino ; 
 TYPE_4__* vino_drvdata ; 
 int /*<<< orphan*/  vino_i2c_adapter ; 

__attribute__((used)) static void vino_module_cleanup(int stage)
{
	switch(stage) {
	case 11:
		video_unregister_device(vino_drvdata->b.vdev);
		vino_drvdata->b.vdev = NULL;
	case 10:
		video_unregister_device(vino_drvdata->a.vdev);
		vino_drvdata->a.vdev = NULL;
	case 9:
		i2c_del_adapter(&vino_i2c_adapter);
	case 8:
		free_irq(SGI_VINO_IRQ, NULL);
	case 7:
		if (vino_drvdata->b.vdev) {
			video_device_release(vino_drvdata->b.vdev);
			vino_drvdata->b.vdev = NULL;
		}
	case 6:
		if (vino_drvdata->a.vdev) {
			video_device_release(vino_drvdata->a.vdev);
			vino_drvdata->a.vdev = NULL;
		}
	case 5:
		/* all entries in dma_cpu dummy table have the same address */
		dma_unmap_single(NULL,
				 vino_drvdata->dummy_desc_table.dma_cpu[0],
				 PAGE_SIZE, DMA_FROM_DEVICE);
		dma_free_coherent(NULL, VINO_DUMMY_DESC_COUNT
				  * sizeof(dma_addr_t),
				  (void *)vino_drvdata->
				  dummy_desc_table.dma_cpu,
				  vino_drvdata->dummy_desc_table.dma);
	case 4:
		free_page(vino_drvdata->dummy_page);
	case 3:
		v4l2_device_unregister(&vino_drvdata->v4l2_dev);
	case 2:
		kfree(vino_drvdata);
	case 1:
		iounmap(vino);
	case 0:
		break;
	default:
		dprintk("vino_module_cleanup(): invalid cleanup stage = %d\n",
			stage);
	}
}