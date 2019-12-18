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
struct whc_std {int num_pointers; int len; struct whc_std* pl_virt; scalar_t__ dma_addr; struct whc_std* bounce_buf; int /*<<< orphan*/  buf_ptr; TYPE_1__* urb; int /*<<< orphan*/  list_node; } ;
struct whc_page_list_entry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct whc {TYPE_2__ wusbhc; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct whc_std*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qset_copy_bounce_to_sg (struct whc*,struct whc_std*) ; 
 int usb_pipeout (int /*<<< orphan*/ ) ; 

void qset_free_std(struct whc *whc, struct whc_std *std)
{
	list_del(&std->list_node);
	if (std->bounce_buf) {
		bool is_out = usb_pipeout(std->urb->pipe);
		dma_addr_t dma_addr;

		if (std->num_pointers)
			dma_addr = le64_to_cpu(std->pl_virt[0].buf_ptr);
		else
			dma_addr = std->dma_addr;

		dma_unmap_single(whc->wusbhc.dev, dma_addr,
				 std->len, is_out ? DMA_TO_DEVICE : DMA_FROM_DEVICE);
		if (!is_out)
			qset_copy_bounce_to_sg(whc, std);
		kfree(std->bounce_buf);
	}
	if (std->pl_virt) {
		if (std->dma_addr)
			dma_unmap_single(whc->wusbhc.dev, std->dma_addr,
					 std->num_pointers * sizeof(struct whc_page_list_entry),
					 DMA_TO_DEVICE);
		kfree(std->pl_virt);
		std->pl_virt = NULL;
	}
	kfree(std);
}