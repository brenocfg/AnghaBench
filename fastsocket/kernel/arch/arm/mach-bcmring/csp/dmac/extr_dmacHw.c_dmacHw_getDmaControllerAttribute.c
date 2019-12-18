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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dmacHw_HANDLE_t ;
typedef  int dmacHw_CONTROLLER_ATTRIB_e ;
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ dmacHw_CBLK_t ;

/* Variables and functions */
 int GetFifoSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacHw_ASSERT (int /*<<< orphan*/ ) ; 
#define  dmacHw_CONTROLLER_ATTRIB_CHANNEL_BUS_WIDTH 132 
#define  dmacHw_CONTROLLER_ATTRIB_CHANNEL_FIFO_SIZE 131 
#define  dmacHw_CONTROLLER_ATTRIB_CHANNEL_MAX_BLOCK_SIZE 130 
#define  dmacHw_CONTROLLER_ATTRIB_CHANNEL_NUM 129 
#define  dmacHw_CONTROLLER_ATTRIB_MASTER_INTF_NUM 128 
 int dmacHw_GET_CHANNEL_DATA_WIDTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacHw_GET_MAX_BLOCK_SIZE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dmacHw_GET_NUM_CHANNEL (int /*<<< orphan*/ ) ; 
 int dmacHw_GET_NUM_INTERFACE (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmacHw_HANDLE_TO_CBLK (int /*<<< orphan*/ ) ; 

uint32_t dmacHw_getDmaControllerAttribute(dmacHw_HANDLE_t handle,	/*  [ IN ]  DMA Channel handle */
					  dmacHw_CONTROLLER_ATTRIB_e attr	/*  [ IN ]  DMA Controler attribute of type  dmacHw_CONTROLLER_ATTRIB_e */
    ) {
	dmacHw_CBLK_t *pCblk = dmacHw_HANDLE_TO_CBLK(handle);

	switch (attr) {
	case dmacHw_CONTROLLER_ATTRIB_CHANNEL_NUM:
		return dmacHw_GET_NUM_CHANNEL(pCblk->module);
	case dmacHw_CONTROLLER_ATTRIB_CHANNEL_MAX_BLOCK_SIZE:
		return (1 <<
			 (dmacHw_GET_MAX_BLOCK_SIZE
			  (pCblk->module, pCblk->module) + 2)) - 8;
	case dmacHw_CONTROLLER_ATTRIB_MASTER_INTF_NUM:
		return dmacHw_GET_NUM_INTERFACE(pCblk->module);
	case dmacHw_CONTROLLER_ATTRIB_CHANNEL_BUS_WIDTH:
		return 32 << dmacHw_GET_CHANNEL_DATA_WIDTH(pCblk->module,
							   pCblk->channel);
	case dmacHw_CONTROLLER_ATTRIB_CHANNEL_FIFO_SIZE:
		return GetFifoSize(handle);
	}
	dmacHw_ASSERT(0);
	return 0;
}