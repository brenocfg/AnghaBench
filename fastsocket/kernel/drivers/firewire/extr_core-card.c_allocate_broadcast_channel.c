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
struct fw_card {int broadcast_channel_allocated; int /*<<< orphan*/  device; int /*<<< orphan*/  bm_transaction_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_device_set_broadcast_channel ; 
 int /*<<< orphan*/  fw_iso_resource_manage (struct fw_card*,int,unsigned long long,int*,int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allocate_broadcast_channel(struct fw_card *card, int generation)
{
	int channel, bandwidth = 0;

	fw_iso_resource_manage(card, generation, 1ULL << 31, &channel,
			       &bandwidth, true, card->bm_transaction_data);
	if (channel == 31) {
		card->broadcast_channel_allocated = true;
		device_for_each_child(card->device, (void *)(long)generation,
				      fw_device_set_broadcast_channel);
	}
}