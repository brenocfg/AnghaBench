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
struct ioatdma_device {int /*<<< orphan*/  (* cleanup_tasklet ) (unsigned long) ;} ;
struct TYPE_2__ {struct ioatdma_device* device; } ;
struct ioat2_dma_chan {TYPE_1__ base; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 scalar_t__ DMA_SUCCESS ; 
 int ioat_is_complete (struct dma_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned long) ; 
 struct ioat2_dma_chan* to_ioat2_chan (struct dma_chan*) ; 

enum dma_status
ioat2_is_complete(struct dma_chan *c, dma_cookie_t cookie,
		     dma_cookie_t *done, dma_cookie_t *used)
{
	struct ioat2_dma_chan *ioat = to_ioat2_chan(c);
	struct ioatdma_device *device = ioat->base.device;

	if (ioat_is_complete(c, cookie, done, used) == DMA_SUCCESS)
		return DMA_SUCCESS;

	device->cleanup_tasklet((unsigned long) ioat);

	return ioat_is_complete(c, cookie, done, used);
}