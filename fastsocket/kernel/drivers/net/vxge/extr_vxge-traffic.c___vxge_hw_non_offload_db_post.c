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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct __vxge_hw_channel {int dummy; } ;
struct __vxge_hw_fifo {TYPE_1__* nofl_db; struct __vxge_hw_channel channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  txdl_ptr; int /*<<< orphan*/  control_0; } ;

/* Variables and functions */
 int VXGE_HW_NODBW_GET_NO_SNOOP (int /*<<< orphan*/ ) ; 
 int VXGE_HW_NODBW_LAST_TXD_NUMBER (int /*<<< orphan*/ ) ; 
 int VXGE_HW_NODBW_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VXGE_HW_NODBW_TYPE_NODBW ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __vxge_hw_non_offload_db_post(struct __vxge_hw_fifo *fifo,
	u64 txdl_ptr, u32 num_txds, u32 no_snoop)
{
	struct __vxge_hw_channel *channel;

	channel = &fifo->channel;

	writeq(VXGE_HW_NODBW_TYPE(VXGE_HW_NODBW_TYPE_NODBW) |
		VXGE_HW_NODBW_LAST_TXD_NUMBER(num_txds) |
		VXGE_HW_NODBW_GET_NO_SNOOP(no_snoop),
		&fifo->nofl_db->control_0);

	mmiowb();

	writeq(txdl_ptr, &fifo->nofl_db->txdl_ptr);

	mmiowb();
}