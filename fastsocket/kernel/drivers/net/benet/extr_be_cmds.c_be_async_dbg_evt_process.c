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
typedef  int u8 ;
typedef  int u32 ;
struct be_mcc_compl {int dummy; } ;
struct be_async_event_qnq {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  valid; } ;
struct be_adapter {TYPE_1__* pdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  qnq_vid; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ASYNC_DEBUG_EVENT_TYPE_QNQ 128 
 int ASYNC_TRAILER_EVENT_TYPE_MASK ; 
 int ASYNC_TRAILER_EVENT_TYPE_SHIFT ; 
 int /*<<< orphan*/  BE_FLAGS_QNQ_ASYNC_EVT_RCVD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void be_async_dbg_evt_process(struct be_adapter *adapter,
		u32 trailer, struct be_mcc_compl *cmp)
{
	u8 event_type = 0;
	struct be_async_event_qnq *evt = (struct be_async_event_qnq *) cmp;

	event_type = (trailer >> ASYNC_TRAILER_EVENT_TYPE_SHIFT) &
		ASYNC_TRAILER_EVENT_TYPE_MASK;

	switch (event_type) {
	case ASYNC_DEBUG_EVENT_TYPE_QNQ:
		if (evt->valid)
			adapter->qnq_vid = le16_to_cpu(evt->vlan_tag);
		adapter->flags |= BE_FLAGS_QNQ_ASYNC_EVT_RCVD;
	break;
	default:
		dev_warn(&adapter->pdev->dev, "Unknown debug event\n");
	break;
	}
}