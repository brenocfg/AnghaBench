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
struct TYPE_3__ {int /*<<< orphan*/  max_packet_size_tx; int /*<<< orphan*/  max_packet_size_rx; int /*<<< orphan*/  protocol; int /*<<< orphan*/  sub_class; int /*<<< orphan*/  interface_index; int /*<<< orphan*/  pid; int /*<<< orphan*/  vid; int /*<<< orphan*/  physical_device_inst; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ HIDDevice ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 

__attribute__((used)) static void log_device(HIDDevice *device)
{
   if (!device)
   {
      RARCH_LOG("NULL device.\n");
   }

   RARCH_LOG("                handle: %d\n", device->handle);
   RARCH_LOG("  physical_device_inst: %d\n", device->physical_device_inst);
   RARCH_LOG("                   vid: 0x%x\n", device->vid);
   RARCH_LOG("                   pid: 0x%x\n", device->pid);
   RARCH_LOG("       interface_index: %d\n", device->interface_index);
   RARCH_LOG("             sub_class: %d\n", device->sub_class);
   RARCH_LOG("              protocol: %d\n", device->protocol);
   RARCH_LOG("    max_packet_size_rx: %d\n", device->max_packet_size_rx);
   RARCH_LOG("    max_packet_size_tx: %d\n", device->max_packet_size_tx);
}