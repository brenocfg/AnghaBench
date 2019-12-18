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
struct hpsb_packet {int /*<<< orphan*/  queue; int /*<<< orphan*/  driver_list; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hpsb_packet*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void hpsb_free_packet(struct hpsb_packet *packet)
{
	if (packet && atomic_dec_and_test(&packet->refcnt)) {
		BUG_ON(!list_empty(&packet->driver_list) ||
		       !list_empty(&packet->queue));
		kfree(packet);
	}
}