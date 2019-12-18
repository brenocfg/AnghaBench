#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_le ;
typedef  int u8 ;
struct vmbus_channel_debug_info {int /*<<< orphan*/  outbound; int /*<<< orphan*/  inbound; int /*<<< orphan*/  clientmonitor_connectionid; int /*<<< orphan*/  clientmonitor_latency; int /*<<< orphan*/  clientmonitor_pending; int /*<<< orphan*/  servermonitor_connectionid; int /*<<< orphan*/  servermonitor_latency; int /*<<< orphan*/  servermonitor_pending; scalar_t__ monitorid; int /*<<< orphan*/  interface_instance; int /*<<< orphan*/  interfacetype; int /*<<< orphan*/  state; int /*<<< orphan*/  relid; } ;
struct TYPE_8__ {int /*<<< orphan*/  if_instance; int /*<<< orphan*/  if_type; } ;
struct TYPE_9__ {scalar_t__ monitorid; TYPE_1__ offer; int /*<<< orphan*/  child_relid; } ;
struct vmbus_channel {int /*<<< orphan*/  outbound; int /*<<< orphan*/  inbound; TYPE_2__ offermsg; int /*<<< orphan*/  state; } ;
struct hv_monitor_page {TYPE_6__** parameter; int /*<<< orphan*/ ** latency; TYPE_3__* trigger_group; } ;
struct TYPE_14__ {scalar_t__ monitor_pages; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {TYPE_4__ u; } ;
struct TYPE_13__ {TYPE_5__ connectionid; } ;
struct TYPE_10__ {int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  hv_ringbuffer_get_debuginfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_7__ vmbus_connection ; 

void vmbus_get_debug_info(struct vmbus_channel *channel,
			      struct vmbus_channel_debug_info *debuginfo)
{
	struct hv_monitor_page *monitorpage;
	u8 monitor_group = (u8)channel->offermsg.monitorid / 32;
	u8 monitor_offset = (u8)channel->offermsg.monitorid % 32;

	debuginfo->relid = channel->offermsg.child_relid;
	debuginfo->state = channel->state;
	memcpy(&debuginfo->interfacetype,
	       &channel->offermsg.offer.if_type, sizeof(uuid_le));
	memcpy(&debuginfo->interface_instance,
	       &channel->offermsg.offer.if_instance,
	       sizeof(uuid_le));

	monitorpage = (struct hv_monitor_page *)vmbus_connection.monitor_pages;

	debuginfo->monitorid = channel->offermsg.monitorid;

	debuginfo->servermonitor_pending =
			monitorpage->trigger_group[monitor_group].pending;
	debuginfo->servermonitor_latency =
			monitorpage->latency[monitor_group][monitor_offset];
	debuginfo->servermonitor_connectionid =
			monitorpage->parameter[monitor_group]
					[monitor_offset].connectionid.u.id;

	monitorpage++;

	debuginfo->clientmonitor_pending =
			monitorpage->trigger_group[monitor_group].pending;
	debuginfo->clientmonitor_latency =
			monitorpage->latency[monitor_group][monitor_offset];
	debuginfo->clientmonitor_connectionid =
			monitorpage->parameter[monitor_group]
					[monitor_offset].connectionid.u.id;

	hv_ringbuffer_get_debuginfo(&channel->inbound, &debuginfo->inbound);
	hv_ringbuffer_get_debuginfo(&channel->outbound, &debuginfo->outbound);
}