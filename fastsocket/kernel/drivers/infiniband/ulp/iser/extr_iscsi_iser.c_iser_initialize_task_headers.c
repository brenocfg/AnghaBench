#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct iser_tx_desc {TYPE_3__* tx_sg; int /*<<< orphan*/  dma_addr; } ;
struct iser_device {TYPE_4__* mr; int /*<<< orphan*/  ib_device; } ;
struct iscsi_task {struct iscsi_iser_task* dd_data; TYPE_1__* conn; } ;
struct iscsi_iser_task {struct iscsi_iser_conn* iser_conn; } ;
struct iscsi_iser_conn {TYPE_2__* ib_conn; } ;
struct TYPE_8__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_7__ {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {struct iser_device* device; } ;
struct TYPE_5__ {struct iscsi_iser_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int iser_initialize_task_headers(struct iscsi_task *task,
						struct iser_tx_desc *tx_desc)
{
	struct iscsi_iser_conn *iser_conn = task->conn->dd_data;
	struct iser_device     *device    = iser_conn->ib_conn->device;
	struct iscsi_iser_task *iser_task = task->dd_data;
	u64 dma_addr;

	dma_addr = ib_dma_map_single(device->ib_device, (void *)tx_desc,
				ISER_HEADERS_LEN, DMA_TO_DEVICE);
	if (ib_dma_mapping_error(device->ib_device, dma_addr))
		return -ENOMEM;

	tx_desc->dma_addr = dma_addr;
	tx_desc->tx_sg[0].addr   = tx_desc->dma_addr;
	tx_desc->tx_sg[0].length = ISER_HEADERS_LEN;
	tx_desc->tx_sg[0].lkey   = device->mr->lkey;

	iser_task->iser_conn		= iser_conn;
	return 0;
}