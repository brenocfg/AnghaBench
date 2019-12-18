#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int line; int max_frame_size; int /*<<< orphan*/  irq_level; int /*<<< orphan*/  io_base; int /*<<< orphan*/  device_name; struct TYPE_5__* next_device; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int MAX_DEVICE_COUNT ; 
 int /*<<< orphan*/  hdlcdev_init (TYPE_1__*) ; 
 int* maxframe ; 
 int mgslpc_device_count ; 
 TYPE_1__* mgslpc_device_list ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void mgslpc_add_device(MGSLPC_INFO *info)
{
	info->next_device = NULL;
	info->line = mgslpc_device_count;
	sprintf(info->device_name,"ttySLP%d",info->line);

	if (info->line < MAX_DEVICE_COUNT) {
		if (maxframe[info->line])
			info->max_frame_size = maxframe[info->line];
	}

	mgslpc_device_count++;

	if (!mgslpc_device_list)
		mgslpc_device_list = info;
	else {
		MGSLPC_INFO *current_dev = mgslpc_device_list;
		while( current_dev->next_device )
			current_dev = current_dev->next_device;
		current_dev->next_device = info;
	}

	if (info->max_frame_size < 4096)
		info->max_frame_size = 4096;
	else if (info->max_frame_size > 65535)
		info->max_frame_size = 65535;

	printk( "SyncLink PC Card %s:IO=%04X IRQ=%d\n",
		info->device_name, info->io_base, info->irq_level);

#if SYNCLINK_GENERIC_HDLC
	hdlcdev_init(info);
#endif
}