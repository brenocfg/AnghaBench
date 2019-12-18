#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hdpvr_device {int /*<<< orphan*/  rec_buff_list; int /*<<< orphan*/  free_buff_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdpvr_cancel_queue (struct hdpvr_device*) ; 
 int /*<<< orphan*/  hdpvr_free_queue (int /*<<< orphan*/ *) ; 

int hdpvr_free_buffers(struct hdpvr_device *dev)
{
	hdpvr_cancel_queue(dev);

	hdpvr_free_queue(&dev->free_buff_list);
	hdpvr_free_queue(&dev->rec_buff_list);

	return 0;
}