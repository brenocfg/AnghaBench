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
struct be_async_event_grp5_qos_link_speed {int dummy; } ;
struct be_async_event_grp5_pvid_state {int dummy; } ;
struct be_async_event_grp5_cos_priority {int dummy; } ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ASYNC_EVENT_COS_PRIORITY 130 
#define  ASYNC_EVENT_PVID_STATE 129 
#define  ASYNC_EVENT_QOS_SPEED 128 
 int ASYNC_TRAILER_EVENT_TYPE_MASK ; 
 int ASYNC_TRAILER_EVENT_TYPE_SHIFT ; 
 int /*<<< orphan*/  be_async_grp5_cos_priority_process (struct be_adapter*,struct be_async_event_grp5_cos_priority*) ; 
 int /*<<< orphan*/  be_async_grp5_pvid_state_process (struct be_adapter*,struct be_async_event_grp5_pvid_state*) ; 
 int /*<<< orphan*/  be_async_grp5_qos_speed_process (struct be_adapter*,struct be_async_event_grp5_qos_link_speed*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void be_async_grp5_evt_process(struct be_adapter *adapter,
		u32 trailer, struct be_mcc_compl *evt)
{
	u8 event_type = 0;

	event_type = (trailer >> ASYNC_TRAILER_EVENT_TYPE_SHIFT) &
		ASYNC_TRAILER_EVENT_TYPE_MASK;

	switch (event_type) {
	case ASYNC_EVENT_COS_PRIORITY:
		be_async_grp5_cos_priority_process(adapter,
		(struct be_async_event_grp5_cos_priority *)evt);
	break;
	case ASYNC_EVENT_QOS_SPEED:
		be_async_grp5_qos_speed_process(adapter,
		(struct be_async_event_grp5_qos_link_speed *)evt);
	break;
	case ASYNC_EVENT_PVID_STATE:
		be_async_grp5_pvid_state_process(adapter,
		(struct be_async_event_grp5_pvid_state *)evt);
	break;
	default:
		dev_warn(&adapter->pdev->dev, "Unknown grp5 event!\n");
		break;
	}
}