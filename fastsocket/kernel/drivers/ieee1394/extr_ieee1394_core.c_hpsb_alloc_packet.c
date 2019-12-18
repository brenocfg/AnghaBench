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
struct hpsb_packet {int generation; size_t allocated_data_size; int /*<<< orphan*/  embedded_data; int /*<<< orphan*/  data; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  queue; int /*<<< orphan*/  driver_list; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hpsb_unused ; 
 struct hpsb_packet* kzalloc (int,int /*<<< orphan*/ ) ; 

struct hpsb_packet *hpsb_alloc_packet(size_t data_size)
{
	struct hpsb_packet *packet;

	data_size = ((data_size + 3) & ~3);

	packet = kzalloc(sizeof(*packet) + data_size, GFP_ATOMIC);
	if (!packet)
		return NULL;

	packet->state = hpsb_unused;
	packet->generation = -1;
	INIT_LIST_HEAD(&packet->driver_list);
	INIT_LIST_HEAD(&packet->queue);
	atomic_set(&packet->refcnt, 1);

	if (data_size) {
		packet->data = packet->embedded_data;
		packet->allocated_data_size = data_size;
	}
	return packet;
}