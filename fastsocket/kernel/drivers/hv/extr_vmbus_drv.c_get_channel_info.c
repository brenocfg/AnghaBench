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
typedef  int /*<<< orphan*/  uuid_le ;
struct TYPE_8__ {int /*<<< orphan*/  bytes_avail_towrite; int /*<<< orphan*/  bytes_avail_toread; int /*<<< orphan*/  current_write_index; int /*<<< orphan*/  current_read_index; int /*<<< orphan*/  current_interrupt_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/  bytes_avail_towrite; int /*<<< orphan*/  bytes_avail_toread; int /*<<< orphan*/  current_write_index; int /*<<< orphan*/  current_read_index; int /*<<< orphan*/  current_interrupt_mask; } ;
struct vmbus_channel_debug_info {TYPE_4__ outbound; TYPE_2__ inbound; int /*<<< orphan*/  clientmonitor_connectionid; int /*<<< orphan*/  clientmonitor_latency; int /*<<< orphan*/  clientmonitor_pending; int /*<<< orphan*/  servermonitor_connectionid; int /*<<< orphan*/  servermonitor_latency; int /*<<< orphan*/  servermonitor_pending; int /*<<< orphan*/  monitorid; int /*<<< orphan*/  interface_instance; int /*<<< orphan*/  interfacetype; int /*<<< orphan*/  state; int /*<<< orphan*/  relid; } ;
struct TYPE_7__ {int /*<<< orphan*/  bytes_avail_towrite; int /*<<< orphan*/  bytes_avail_toread; int /*<<< orphan*/  write_idx; int /*<<< orphan*/  read_idx; int /*<<< orphan*/  int_mask; } ;
struct TYPE_5__ {int /*<<< orphan*/  bytes_avail_towrite; int /*<<< orphan*/  bytes_avail_toread; int /*<<< orphan*/  write_idx; int /*<<< orphan*/  read_idx; int /*<<< orphan*/  int_mask; } ;
struct hv_device_info {TYPE_3__ outbound; TYPE_1__ inbound; int /*<<< orphan*/  client_monitor_conn_id; int /*<<< orphan*/  client_monitor_latency; int /*<<< orphan*/  client_monitor_pending; int /*<<< orphan*/  server_monitor_conn_id; int /*<<< orphan*/  server_monitor_latency; int /*<<< orphan*/  server_monitor_pending; int /*<<< orphan*/  monitor_id; int /*<<< orphan*/  chn_instance; int /*<<< orphan*/  chn_type; int /*<<< orphan*/  chn_state; int /*<<< orphan*/  chn_id; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmbus_get_debug_info (int /*<<< orphan*/ ,struct vmbus_channel_debug_info*) ; 

__attribute__((used)) static void get_channel_info(struct hv_device *device,
			     struct hv_device_info *info)
{
	struct vmbus_channel_debug_info debug_info;

	if (!device->channel)
		return;

	vmbus_get_debug_info(device->channel, &debug_info);

	info->chn_id = debug_info.relid;
	info->chn_state = debug_info.state;
	memcpy(&info->chn_type, &debug_info.interfacetype,
	       sizeof(uuid_le));
	memcpy(&info->chn_instance, &debug_info.interface_instance,
	       sizeof(uuid_le));

	info->monitor_id = debug_info.monitorid;

	info->server_monitor_pending = debug_info.servermonitor_pending;
	info->server_monitor_latency = debug_info.servermonitor_latency;
	info->server_monitor_conn_id = debug_info.servermonitor_connectionid;

	info->client_monitor_pending = debug_info.clientmonitor_pending;
	info->client_monitor_latency = debug_info.clientmonitor_latency;
	info->client_monitor_conn_id = debug_info.clientmonitor_connectionid;

	info->inbound.int_mask = debug_info.inbound.current_interrupt_mask;
	info->inbound.read_idx = debug_info.inbound.current_read_index;
	info->inbound.write_idx = debug_info.inbound.current_write_index;
	info->inbound.bytes_avail_toread =
		debug_info.inbound.bytes_avail_toread;
	info->inbound.bytes_avail_towrite =
		debug_info.inbound.bytes_avail_towrite;

	info->outbound.int_mask =
		debug_info.outbound.current_interrupt_mask;
	info->outbound.read_idx = debug_info.outbound.current_read_index;
	info->outbound.write_idx = debug_info.outbound.current_write_index;
	info->outbound.bytes_avail_toread =
		debug_info.outbound.bytes_avail_toread;
	info->outbound.bytes_avail_towrite =
		debug_info.outbound.bytes_avail_towrite;
}