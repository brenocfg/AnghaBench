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
struct iser_rx_desc {int /*<<< orphan*/  dma_addr; } ;
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct iser_conn {struct iser_rx_desc* rx_descs; struct iser_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ISER_QP_MAX_RECV_DTOS ; 
 int /*<<< orphan*/  ISER_RX_PAYLOAD_SIZE ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iser_rx_desc*) ; 

void iser_free_rx_descriptors(struct iser_conn *ib_conn)
{
	int i;
	struct iser_rx_desc *rx_desc;
	struct iser_device *device = ib_conn->device;

	if (!ib_conn->rx_descs)
		return;

	rx_desc = ib_conn->rx_descs;
	for (i = 0; i < ISER_QP_MAX_RECV_DTOS; i++, rx_desc++)
		ib_dma_unmap_single(device->ib_device, rx_desc->dma_addr,
			ISER_RX_PAYLOAD_SIZE, DMA_FROM_DEVICE);
	kfree(ib_conn->rx_descs);
}