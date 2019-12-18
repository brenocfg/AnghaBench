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
struct iser_tx_desc {scalar_t__ type; int /*<<< orphan*/  dma_addr; } ;
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct iser_conn {int /*<<< orphan*/  post_send_buf_count; struct iser_device* device; } ;
struct iscsi_task {TYPE_1__* hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc_cache; } ;
struct TYPE_3__ {scalar_t__ itt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ ISCSI_TX_CONTROL ; 
 scalar_t__ ISCSI_TX_DATAOUT ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 scalar_t__ RESERVED_ITT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ig ; 
 int /*<<< orphan*/  iscsi_put_task (struct iscsi_task*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct iser_tx_desc*) ; 

void iser_snd_completion(struct iser_tx_desc *tx_desc,
			struct iser_conn *ib_conn)
{
	struct iscsi_task *task;
	struct iser_device *device = ib_conn->device;

	if (tx_desc->type == ISCSI_TX_DATAOUT) {
		ib_dma_unmap_single(device->ib_device, tx_desc->dma_addr,
					ISER_HEADERS_LEN, DMA_TO_DEVICE);
		kmem_cache_free(ig.desc_cache, tx_desc);
	}

	atomic_dec(&ib_conn->post_send_buf_count);

	if (tx_desc->type == ISCSI_TX_CONTROL) {
		/* this arithmetic is legal by libiscsi dd_data allocation */
		task = (void *) ((long)(void *)tx_desc -
				  sizeof(struct iscsi_task));
		if (task->hdr->itt == RESERVED_ITT)
			iscsi_put_task(task);
	}
}