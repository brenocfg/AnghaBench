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
struct usb_request {scalar_t__ length; int /*<<< orphan*/  dma; } ;
struct s3c_hsotg_req {scalar_t__ mapped; struct usb_request req; } ;
struct s3c_hsotg_ep {scalar_t__ dir_in; } ;
struct s3c_hsotg {int /*<<< orphan*/  dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ADDR_INVALID ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void s3c_hsotg_unmap_dma(struct s3c_hsotg *hsotg,
				struct s3c_hsotg_ep *hs_ep,
				struct s3c_hsotg_req *hs_req)
{
	struct usb_request *req = &hs_req->req;
	enum dma_data_direction dir;

	dir = hs_ep->dir_in ? DMA_TO_DEVICE : DMA_FROM_DEVICE;

	/* ignore this if we're not moving any data */
	if (hs_req->req.length == 0)
		return;

	if (hs_req->mapped) {
		/* we mapped this, so unmap and remove the dma */

		dma_unmap_single(hsotg->dev, req->dma, req->length, dir);

		req->dma = DMA_ADDR_INVALID;
		hs_req->mapped = 0;
	} else {
		dma_sync_single(hsotg->dev, req->dma, req->length, dir);
	}
}