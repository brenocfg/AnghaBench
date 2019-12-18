#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct queue_entry {TYPE_2__* queue; TYPE_1__* skb; } ;
struct TYPE_4__ {int usb_maxpacket; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int roundup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rt73usb_get_tx_data_len(struct queue_entry *entry)
{
	int length;

	/*
	 * The length _must_ be a multiple of 4,
	 * but it must _not_ be a multiple of the USB packet size.
	 */
	length = roundup(entry->skb->len, 4);
	length += (4 * !(length % entry->queue->usb_maxpacket));

	return length;
}